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
    int i;
    for (i = 0; i < num_players; i++) {
      if (player_pers[i].player_id == 237) {
        printf("Player ID: %d, Player PER: %lf\n", player_pers[i].player_id,
               player_pers[i].per);
      }
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
    MPI_Bcast(&num_games, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int *sendcounts = (int *)malloc(comm_sz * sizeof(int));
    int *process_displacements = (int *)malloc(comm_sz * sizeof(int));

    int chunk_size = num_games / (comm_sz - 1);
    int remainder = num_games % (comm_sz - 1);
    sendcounts[0] = 0;
    process_displacements[0] = 0;
    for (int i = 1; i < comm_sz; i++) {
      sendcounts[i] = chunk_size + (i <= remainder ? 1 : 0);
      process_displacements[i] =
          (i > 0) ? process_displacements[i - 1] + sendcounts[i - 1] : 0;
    }

    int local_count = sendcounts[my_rank];
    game_t *local_games = (game_t *)malloc(local_count * sizeof(game_t));
    if (my_rank == 0) {
      MPI_Scatterv(games, sendcounts, process_displacements, mpi_game_obj,
                   MPI_IN_PLACE, 0, mpi_game_obj, 0, MPI_COMM_WORLD);
    } else {
      MPI_Scatterv(games, sendcounts, process_displacements, mpi_game_obj,
                   local_games, local_count, mpi_game_obj, 0, MPI_COMM_WORLD);
      HashItem *local_player_agg_map =
          compute_season_aggregates(local_games, local_count);
      HashItem *current_item, *tmp;
      HASH_ITER(hh, local_player_agg_map, current_item, tmp) {}
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
