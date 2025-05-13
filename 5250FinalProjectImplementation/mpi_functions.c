#include "csvutils.h"
#include "mpi.h"
#include "per_engine.h"
/**
 * Broadcast the game count to all processes
 *
 * @param num_games pointer to an integer containing the actual game count
 */
void broadcast_game_count(int *num_games) {
  MPI_Bcast(num_games, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

/**
 * Compute sendcounts and displacements for any array of num_item size
 *
 * @param sendcounts array of ints where the sendcounts to each process will be
 * stored
 * @param process_displacements array of ints where the offset each process
 * should start reading from should exist
 * @param num_item the number of items to scatter
 * @param comm_sz number of processes to scatter to
 */
void compute_sendcounts_and_displacements(int *sendcounts,
                                          int *process_displacements,
                                          int num_item, int comm_sz) {
  // Determine size each chunk should get
  int chunk_size = num_item / (comm_sz - 1);
  // Determine whats left after division
  int remainder = num_item % (comm_sz - 1);
  // Set 0 to get no items. 0 is for bookeeping
  sendcounts[0] = 0;
  process_displacements[0] = 0;
  // loop through all processes starting from 1 onwards
  for (int i = 1; i < comm_sz; i++) {
    // Assign size and 1 of remainder to all processes at the start until
    // remainder is satisfied
    sendcounts[i] = chunk_size + (i <= remainder ? 1 : 0);
    // Set displacement based on previous displacement and previous send count
    process_displacements[i] =
        (i > 0) ? process_displacements[i - 1] + sendcounts[i - 1] : 0;
  }
}

/**
 * Scatter game array to all processes evenly
 *
 * @param my_rank current process number
 * @param sendcounts array of ints where the sendcount for each process is
 * stored
 * @param process_displacements array of ints where the displacement for each
 * process is stored
 * @param mpi_game_obj NPI_Datatype for game_t
 * @param local_games array where the games received will be stored for each
 * process
 * @param local_count the number of games to be received
 * @param games the global game array containing all games
 */
void scatter_game_array(int my_rank, int *sendcounts,
                        int *process_displacements, MPI_Datatype mpi_game_obj,
                        game_t *local_games, int local_count, game_t *games) {
  // Check if 0. 0 deoesnt receive anything
  if (my_rank == 0) {
    // Run the scatter with MPI_IN_PLACE to tell MPI 0 receives nothing
    MPI_Scatterv(games, sendcounts, process_displacements, mpi_game_obj,
                 MPI_IN_PLACE, 0, mpi_game_obj, 0, MPI_COMM_WORLD);
  } else {
    // Scatter array games to all procs
    MPI_Scatterv(games, sendcounts, process_displacements, mpi_game_obj,
                 local_games, local_count, mpi_game_obj, 0, MPI_COMM_WORLD);
  }
}

/**
 * Compute global average of uper
 *
 * @param my_rank current process number
 * @param global_average_uper pointer to where global uper average will be
 * stored
 * @param total_uper pointer to local total on any given process
 * @param global_total_uper pointer to where the global total will be stored
 * @param total_num_players total players for calculating average
 */
void get_global_uper_avg(int my_rank, double *global_average_uper,
                         double *total_uper, double *global_total_uper,
                         int total_num_players) {
  // Reduce to global total
  MPI_Reduce(total_uper, global_total_uper, 1, MPI_DOUBLE, MPI_SUM, 0,
             MPI_COMM_WORLD);
  // If we are 0 we have the global total so compute average
  if (my_rank == 0) {
    *global_average_uper = *global_total_uper / (double)total_num_players;
  }
  // Broadcast the global average to other procs
  MPI_Bcast(global_average_uper, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
}
/**
 * Scatter player and agg array to all processes evenly
 *
 * @param my_rank current process number
 * @param final_scatter_sendcounts array of ints where the sendcount for each
 * process is stored
 * @param final_scatter_process_displacements array of ints where the
 * displacement for each process is stored
 * @param mpi_player_and_agg_obj MPI_Datatype for player_and_agg_t
 * @param local_final_player_aggs array where player aggs will be stored on each
 * proc
 * @param local_player_final_count the number of players to be received
 * @param complete_player_agg_array the global player agg array containing all
 * player aggs
 */
void scatter_player_and_agg(int my_rank,
                            player_and_agg_t *complete_player_agg_array,
                            int *final_scatter_sendcounts,
                            int *final_scatter_process_displacements,
                            MPI_Datatype mpi_player_and_agg_obj,
                            player_and_agg_t *local_final_player_aggs,
                            int local_player_final_count) {
  // If 0 we arent receiving anything
  if (my_rank == 0) {
    // Call scatter with MPI_IN_PLACE to specify we wont get anything
    MPI_Scatterv(complete_player_agg_array, final_scatter_sendcounts,
                 final_scatter_process_displacements, mpi_player_and_agg_obj,
                 MPI_IN_PLACE, 0, mpi_player_and_agg_obj, 0, MPI_COMM_WORLD);
  } else {
    // Call scatter to get even amount from global array on 0
    MPI_Scatterv(complete_player_agg_array, final_scatter_sendcounts,
                 final_scatter_process_displacements, mpi_player_and_agg_obj,
                 local_final_player_aggs, local_player_final_count,
                 mpi_player_and_agg_obj, 0, MPI_COMM_WORLD);
  }
}

/**
 * Broadcast the player count to all processes
 *
 * @param actual_player_count pointer to an integer containing the actual player
 * count
 */
void broadcast_actual_player_count(int *actual_player_count) {
  // Broadcast with MPI
  MPI_Bcast(actual_player_count, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

/**
 * Gather player counts on process 0 for computing total player array
 *
 * @param my_rank rank of the current process
 * @param player_counts pointer to an array where the player counts in each
 * local array will be
 * @param comm_sz total num of processes
 * @param player_count pointer to an integer contianing local player count
 */
void gather_player_counts(int my_rank, int **player_counts, int comm_sz,
                          int *player_count) {
  // If 0 intiialize the global player counts array
  if (my_rank == 0) {
    *player_counts = malloc(comm_sz * sizeof(int));
  }
  // Gather the player counts on 0
  MPI_Gather(player_count, 1, MPI_INT, *player_counts, 1, MPI_INT, 0,
             MPI_COMM_WORLD);
}

/**
 * Compute displacements for gathering players on 0
 *
 * @param total_players pointer to where the total player count will be stored
 * @param gather_player_displacements pointer to array which will contain the
 * displacements where each process will leave thier items
 * @param global_players_array pointer to array which will be initialized to fit
 * all players
 * @param comm_sz num processes
 * @param player_counts array containing the player counts for each process
 */
void compute_gather_player_displacements(
    int **gather_player_displacements, int comm_sz, int *total_players,
    player_and_agg_t **global_players_array, int *player_counts) {
  // Initialize displacements array
  *gather_player_displacements = malloc(comm_sz * sizeof(int));
  // 0 doesnt displace anything
  (*gather_player_displacements)[0] = 0;
  // For each process compute its gather displacement
  for (int i = 1; i < comm_sz; i++) {
    // Compute its displacement based on how much each process has
    (*gather_player_displacements)[i] =
        (*gather_player_displacements)[i - 1] + player_counts[i - 1];
  }
  // Get the total count based on the last processes count and displacment
  *total_players =
      (*gather_player_displacements)[comm_sz - 1] + player_counts[comm_sz - 1];
  // Initialize global player array to total players
  *global_players_array = malloc(*total_players * sizeof(player_and_agg_t));
}

/**
 * Compute displacements for gathering players on 0
 *
 * @param my_rank local process number
 * @param local_count count of games each process will have
 * @param mpi_game_obj MPI_Datatype of game_t
 * @param local_games array to store the local games to
 * @param process_displacements displacement to start reading from
 * @param record_size size of each record in bytes
 * @param player_count pointer to store number of players in each local block
 * @param local_player_agg_array pointer to array where player aggs from games
 * will be stored
 */
void read_games_parallel(int my_rank, int local_count,
                         MPI_Datatype mpi_game_obj, game_t *local_games,
                         int *process_displacements, size_t record_size,
                         int *player_count,
                         player_and_agg_t **local_player_agg_array) {
  // Initialize MPI IO file open
  MPI_File fh;
  MPI_File_open(MPI_COMM_WORLD, "1.bin", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
  // Check if 0 and receiving, 0 doesnt do reading
  if (my_rank > 0 && local_count > 0) {
    // Get the offset to start at
    MPI_Offset offset_bytes =
        (MPI_Offset)process_displacements[my_rank] * record_size;
    // Read at offset amount of bytes
    MPI_File_read_at(fh, offset_bytes, local_games, local_count, mpi_game_obj,
                     MPI_STATUS_IGNORE);
    // Compute local agg based on this game list
    *local_player_agg_array =
        compute_local_player_agg_array(local_games, local_count, player_count);
  }
  // Close the file
  MPI_File_close(&fh);
}
