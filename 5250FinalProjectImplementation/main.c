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
  MPI_Datatype mpi_game_obj = create_game_object();
  MPI_Datatype mpi_player_and_agg_obj =
      create_player_stat_and_agg_object(mpi_stat_agg_obj);
  double time_start;
  if (my_rank == 0) {
    time_start = MPI_Wtime();
  }
  if (comm_sz == 1) {
    // Serial implementation:
    FILE *file = fopen("1.bin", "rb");
    int num_games;
    game_t *games = read_games(file, &num_games);
    fclose(file);
    HashItem *player_agg_map = compute_season_aggregates(games, num_games);
    int num_players;
    per_object_t *player_pers =
        compute_player_pers(&player_agg_map, &num_players);
    int i;
    for (i = 0; i < num_players; i++) {
      printf("Player ID: %d, Player PER %lf\n", player_pers[i].player_id,
             player_pers[i].per);
    }
  } else {
    int num_games = 0;
    int record_size = sizeof(game_t);

    if (my_rank == 0) {
      get_num_games(record_size, &num_games);
    }
    broadcast_game_count(&num_games);
    int *sendcounts = malloc(comm_sz * sizeof(int));
    int *process_displacements = malloc(comm_sz * sizeof(int));
    compute_sendcounts_and_displacements(sendcounts, process_displacements,
                                         num_games, comm_sz);
    int local_count = sendcounts[my_rank];
    game_t *local_games = malloc(local_count * sizeof(game_t));
    player_and_agg_t *local_player_agg_array = NULL;
    int player_count = 0;
    read_games_parallel(my_rank, local_count, mpi_game_obj, local_games,
                        process_displacements, record_size, &player_count,
                        &local_player_agg_array);
    int *player_counts = NULL;
    gather_player_counts(my_rank, &player_counts, comm_sz, &player_count);
    int *gather_player_displacements = NULL;
    player_and_agg_t *global_players_array = NULL;
    int total_players = 0;
    if (my_rank == 0) {
      compute_gather_player_displacements(&gather_player_displacements, comm_sz,
                                          &total_players, &global_players_array,
                                          player_counts);
    }

    MPI_Gatherv(local_player_agg_array, player_count, mpi_player_and_agg_obj,
                global_players_array, player_counts,
                gather_player_displacements, mpi_player_and_agg_obj, 0,
                MPI_COMM_WORLD);
    player_and_agg_t *complete_player_agg_array = NULL;
    int actual_player_count;
    if (my_rank == 0) {
      join_player_aggs_to_map(&actual_player_count, total_players,
                              global_players_array, &complete_player_agg_array);
    }
    broadcast_actual_player_count(&actual_player_count);
    int *final_scatter_sendcounts = (int *)malloc(comm_sz * sizeof(int));
    int *final_scatter_process_displacements =
        (int *)malloc(comm_sz * sizeof(int));

    compute_sendcounts_and_displacements(final_scatter_sendcounts,
                                         final_scatter_process_displacements,
                                         actual_player_count, comm_sz);
    int local_player_final_count = final_scatter_sendcounts[my_rank];
    player_and_agg_t *local_final_player_aggs = (player_and_agg_t *)malloc(
        local_player_final_count * sizeof(player_and_agg_t));
    scatter_player_and_agg(
        my_rank, complete_player_agg_array, final_scatter_sendcounts,
        final_scatter_process_displacements, mpi_player_and_agg_obj,
        local_final_player_aggs, local_player_final_count);
    double total_uper = 0.0;
    double global_total_uper = 0.0;
    double global_average_uper = 0.0;
    per_object_t *local_uper_array = compute_player_upers_array(
        local_final_player_aggs, local_player_final_count, &total_uper);
    get_global_uper_avg(my_rank, &global_average_uper, &total_uper,
                        &global_total_uper, actual_player_count);
    adjust_uper_array(local_player_final_count, local_uper_array,
                      global_average_uper);
    int i;
    for (int r = 0; r < comm_sz; r++) {
      if (r == my_rank) {
        for (i = 0; i < local_player_final_count; i++) {
          printf("(%d, %lf)\n", local_uper_array[i].player_id,
                 local_uper_array[i].per);
        }
        fflush(stdout); // Ensure output is flushed
      }
      MPI_Barrier(MPI_COMM_WORLD); // Synchronize
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
