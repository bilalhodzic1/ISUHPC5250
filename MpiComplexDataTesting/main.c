#include "main.h"
#include <mpi.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  stat_agg_t data;
  per_object_t per;
  MPI_Datatype mpi_struct = create_stat_object();
  MPI_Datatype mpi_per_obj = create_player_per_object();
  if (rank == 0) {
    // Initialize the structure
    data.ast_agg = 42;
    data.mins_agg = 3.14f;
    // Send structure to process 1
    send_stat_agg(&data, 1, mpi_struct);
    per.per = 882.222;
    per.player_id = 235;
    send_player_per(&per, 1, mpi_per_obj);
  } else if (rank == 1) {
    // Receive the structure
    recv_stat_agg(&data, 0, mpi_struct);
    recv_player_per(&per, 0, mpi_per_obj);

    // Print the received data
    printf("Received structure:\n");
    printf("assist: %d\n", data.ast_agg);
    printf("mins_agg: %f\n", data.mins_agg);
    printf("Player id: %d\n", per.player_id);
    printf("Player per %lf\n", per.per);
  }

  // Free the custom MPI data type
  MPI_Type_free(&mpi_struct);

  MPI_Finalize();
  return 0;
}
