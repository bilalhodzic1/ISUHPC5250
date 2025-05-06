#include "csvutils.h"
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
