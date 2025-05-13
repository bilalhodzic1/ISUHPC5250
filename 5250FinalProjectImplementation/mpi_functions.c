#include "csvutils.h"
#include "mpi.h"
#include "per_engine.h"

void broadcast_game_count(int *num_games) {
  MPI_Bcast(num_games, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

void compute_sendcounts_and_displacements(int *sendcounts,
                                          int *process_displacements,
                                          int num_item, int comm_sz) {
  int chunk_size = num_item / (comm_sz - 1);
  int remainder = num_item % (comm_sz - 1);
  sendcounts[0] = 0;
  process_displacements[0] = 0;
  for (int i = 1; i < comm_sz; i++) {
    sendcounts[i] = chunk_size + (i <= remainder ? 1 : 0);
    process_displacements[i] =
        (i > 0) ? process_displacements[i - 1] + sendcounts[i - 1] : 0;
  }
}

void scatter_game_array(int my_rank, int *sendcounts,
                        int *process_displacements, MPI_Datatype mpi_game_obj,
                        game_t *local_games, int local_count, game_t *games) {
  if (my_rank == 0) {
    MPI_Scatterv(games, sendcounts, process_displacements, mpi_game_obj,
                 MPI_IN_PLACE, 0, mpi_game_obj, 0, MPI_COMM_WORLD);
  } else {
    MPI_Scatterv(games, sendcounts, process_displacements, mpi_game_obj,
                 local_games, local_count, mpi_game_obj, 0, MPI_COMM_WORLD);
  }
}
void get_global_uper_avg(int my_rank, double *global_average_uper,
                         double *total_uper, double *global_total_uper,
                         int total_num_players) {
  MPI_Reduce(total_uper, global_total_uper, 1, MPI_DOUBLE, MPI_SUM, 0,
             MPI_COMM_WORLD);
  if (my_rank == 0) {
    *global_average_uper = *global_total_uper / (double)total_num_players;
  }
  MPI_Bcast(global_average_uper, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
}

void scatter_player_and_agg(int my_rank,
                            player_and_agg_t *complete_player_agg_array,
                            int *final_scatter_sendcounts,
                            int *final_scatter_process_displacements,
                            MPI_Datatype mpi_player_and_agg_obj,
                            player_and_agg_t *local_final_player_aggs,
                            int local_player_final_count) {
  if (my_rank == 0) {
    MPI_Scatterv(complete_player_agg_array, final_scatter_sendcounts,
                 final_scatter_process_displacements, mpi_player_and_agg_obj,
                 MPI_IN_PLACE, 0, mpi_player_and_agg_obj, 0, MPI_COMM_WORLD);
  } else {
    MPI_Scatterv(complete_player_agg_array, final_scatter_sendcounts,
                 final_scatter_process_displacements, mpi_player_and_agg_obj,
                 local_final_player_aggs, local_player_final_count,
                 mpi_player_and_agg_obj, 0, MPI_COMM_WORLD);
  }
}
void broadcast_actual_player_count(int *actual_player_count) {
  MPI_Bcast(actual_player_count, 1, MPI_INT, 0, MPI_COMM_WORLD);
}
void gather_player_counts(int my_rank, int **player_counts, int comm_sz,
                          int *player_count) {
  if (my_rank == 0) {
    *player_counts = malloc(comm_sz * sizeof(int));
  }
  MPI_Gather(player_count, 1, MPI_INT, *player_counts, 1, MPI_INT, 0,
             MPI_COMM_WORLD);
}
void compute_gather_player_displacements(
    int **gather_player_displacements, int comm_sz, int *total_players,
    player_and_agg_t **global_players_array, int *player_counts) {
  *gather_player_displacements = malloc(comm_sz * sizeof(int));
  (*gather_player_displacements)[0] = 0;
  for (int i = 1; i < comm_sz; i++) {
    (*gather_player_displacements)[i] =
        (*gather_player_displacements)[i - 1] + player_counts[i - 1];
  }
  *total_players =
      (*gather_player_displacements)[comm_sz - 1] + player_counts[comm_sz - 1];

  *global_players_array = malloc(*total_players * sizeof(player_and_agg_t));
}

void read_games_parallel(int my_rank, int local_count,
                         MPI_Datatype mpi_game_obj, game_t *local_games,
                         int *process_displacements, size_t record_size,
                         int *player_count,
                         player_and_agg_t **local_player_agg_array) {
  MPI_File fh;
  MPI_File_open(MPI_COMM_WORLD, "1.bin", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
  if (my_rank > 0 && local_count > 0) {
    MPI_Offset offset_bytes =
        (MPI_Offset)process_displacements[my_rank] * record_size;

    MPI_File_read_at(fh, offset_bytes, local_games, local_count, mpi_game_obj,
                     MPI_STATUS_IGNORE);
    *local_player_agg_array =
        compute_local_player_agg_array(local_games, local_count, player_count);
  }
  MPI_File_close(&fh);
}
