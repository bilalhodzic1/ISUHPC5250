/*
OUTLINE:

READ CSV into data rows for processing
    CSV is ordered by season/player

Compute game PER using simplified formula
    Maybe I will extend this im not sure
Get game_id player_id and PER from this

Compute in parallel the UPER for a player in each season
    UPER is composed of many aggregate stats
    Should be possible to compute these in parallel (About 2 million total data
points) How to do this with MPI to maximize parallelization? Is this even a good
idea Wait for all seasons to be computed Separate by season to get num over 15
UPER per season Determin scaling factor Go through each UPER and multiple the
scalaing factor
*/
#include "csvutils.h"
#include "hashmap.h"
#include "mpi.h"
#include "per_engine.h"
int main(int argc, char *argv[]) {
  int comm_sz, my_rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Datatype mpi_stat_agg_obj = create_stat_object();
  // MPI_Datatype mpi_per_obj = create_player_per_object();
  MPI_Datatype mpi_game_obj = create_game_object();
  MPI_Datatype mpi_player_and_agg_obj =
      create_player_stat_and_agg_object(mpi_stat_agg_obj);
  double time_start;
  if (my_rank == 0) {
    time_start = MPI_Wtime();
  }
  if (comm_sz == 1) {
    // Serial implementation:
    FILE *file = fopen("1.csv", "r");
    int num_games;
    game_t *games = read_games(file, &num_games);
    fclose(file);
    HashItem *player_agg_map = compute_season_aggregates(games, num_games);
    int num_players;
    per_object_t *player_pers =
        compute_player_pers(&player_agg_map, &num_players);
    printf("%-12s %12s\n", "Player ID", "Player PER"); // Header
    printf("------------ ------------\n");             // Separator

    for (int i = 0; i < num_players; i++) {
      printf("%12d %12.2f\n", player_pers[i].player_id, player_pers[i].per);
    }
  } else {
    FILE *file;
    int num_games;
    game_t *games;
    if (my_rank == 0) {
      file = fopen("1.csv", "r");
      games = read_games(file, &num_games);
      fclose(file);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    broadcast_game_count(&num_games);
    int *sendcounts = (int *)malloc(comm_sz * sizeof(int));
    int *process_displacements = (int *)malloc(comm_sz * sizeof(int));

    compute_sendcounts_and_displacements(sendcounts, process_displacements,
                                         num_games, comm_sz);

    int local_count = sendcounts[my_rank];
    game_t *local_games = (game_t *)malloc(local_count * sizeof(game_t));
    player_and_agg_t *local_player_agg_array = NULL;
    int player_count;
    if (my_rank == 0) {
      scatter_game_array(my_rank, sendcounts, process_displacements,
                         mpi_game_obj, NULL, local_count, games);
    } else {
      scatter_game_array(my_rank, sendcounts, process_displacements,
                         mpi_game_obj, local_games, local_count, games);
      local_player_agg_array = compute_local_player_agg_array(
          local_games, local_count, &player_count);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    int *player_counts = NULL;
    if (my_rank == 0) {
      player_counts = malloc(comm_sz * sizeof(int));
    }
    MPI_Gather(&player_count, 1, MPI_INT, player_counts, 1, MPI_INT, 0,
               MPI_COMM_WORLD);
    int *gather_player_displacements = NULL;
    player_and_agg_t *global_players_array = NULL;
    int total_players = 0;
    if (my_rank == 0) {
      gather_player_displacements = malloc(comm_sz * sizeof(int));
      gather_player_displacements[0] = 0;
      for (int i = 1; i < comm_sz; i++) {
        gather_player_displacements[i] =
            gather_player_displacements[i - 1] + player_counts[i - 1];
      }
      total_players =
          gather_player_displacements[comm_sz - 1] + player_counts[comm_sz - 1];

      global_players_array = malloc(total_players * sizeof(player_and_agg_t));
    }
    MPI_Gatherv(local_player_agg_array, player_count, mpi_player_and_agg_obj,
                global_players_array, player_counts,
                gather_player_displacements, mpi_player_and_agg_obj, 0,
                MPI_COMM_WORLD);
    if (my_rank == 0) {
      int actual_player_count = 0;
      for (int i = 0; i < total_players; i++) {
        HashItem *complete_player_agg_map = NULL;
        HashItem *item =
            find(global_players_array[i].player_id, &complete_player_agg_map);
        if (item) {
          stat_agg_t *existing_stat_agg = item->value;
          stat_agg_t new_stat_agg = global_players_array[i].player_agg_stats;
          existing_stat_agg->fgm_agg += new_stat_agg.fgm_agg;
          existing_stat_agg->ftm_agg += new_stat_agg.ftm_agg;
          existing_stat_agg->oreb_agg += new_stat_agg.oreb_agg;
          existing_stat_agg->dreb_agg += new_stat_agg.dreb_agg;
          existing_stat_agg->ast_agg += new_stat_agg.ast_agg;
          existing_stat_agg->stl_agg += new_stat_agg.stl_agg;
          existing_stat_agg->blk_agg += new_stat_agg.blk_agg;
          existing_stat_agg->fga_agg += new_stat_agg.fga_agg;
          existing_stat_agg->fta_agg += new_stat_agg.fta_agg;
          existing_stat_agg->to_agg += new_stat_agg.to_agg;
          existing_stat_agg->pf_agg += new_stat_agg.pf_agg;
          existing_stat_agg->mins_agg += new_stat_agg.mins_agg;
        } else {
          actual_player_count++;
          insert(global_players_array[i].player_id,
                 &(global_players_array[i].player_agg_stats),
                 &complete_player_agg_map);
        }
      }
    }
  }
  MPI_Barrier(MPI_COMM_WORLD);
  if (my_rank == 0) {
    double time_end = MPI_Wtime();
    double time_elapsed = time_end - time_start;
    printf(" Elapsed time = %20.13e\n", time_elapsed);
  }
  MPI_Finalize();
  return 0;
}
