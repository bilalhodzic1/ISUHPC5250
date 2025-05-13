#include "csvutils.h"
#include "mpi.h"
#include "per_engine.h"

/**
 * Create a MPI_Datatype definition for a stat agg object
 *
 * @return the MPI_Datatype for a stat_agg_t
 */
MPI_Datatype create_stat_object() {
  MPI_Datatype mpi_stat_agg;
  int block_lengths[13] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  MPI_Aint displacements[13];
  MPI_Datatype types[13] = {MPI_INT, MPI_INT,   MPI_INT, MPI_INT, MPI_INT,
                            MPI_INT, MPI_INT,   MPI_INT, MPI_INT, MPI_INT,
                            MPI_INT, MPI_FLOAT, MPI_INT};

  displacements[0] = offsetof(stat_agg_t, fgm_agg);
  displacements[1] = offsetof(stat_agg_t, ftm_agg);
  displacements[2] = offsetof(stat_agg_t, oreb_agg);
  displacements[3] = offsetof(stat_agg_t, dreb_agg);
  displacements[4] = offsetof(stat_agg_t, ast_agg);
  displacements[5] = offsetof(stat_agg_t, stl_agg);
  displacements[6] = offsetof(stat_agg_t, blk_agg);
  displacements[7] = offsetof(stat_agg_t, fga_agg);
  displacements[8] = offsetof(stat_agg_t, fta_agg);
  displacements[9] = offsetof(stat_agg_t, to_agg);
  displacements[10] = offsetof(stat_agg_t, pf_agg);
  displacements[11] = offsetof(stat_agg_t, mins_agg);
  displacements[12] = offsetof(stat_agg_t, player_id);

  MPI_Type_create_struct(13, block_lengths, displacements, types,
                         &mpi_stat_agg);
  MPI_Type_commit(&mpi_stat_agg);

  return mpi_stat_agg;
}

/**
 * Create a MPI_Datatype definition for a per object
 *
 * @return the MPI_Datatype for a per_object_t
 */
MPI_Datatype create_player_per_object() {
  MPI_Datatype mpi_per_object;
  int block_lengths[3] = {1, 1, 1};
  MPI_Aint displacements[3];
  MPI_Datatype types[3] = {MPI_INT, MPI_DOUBLE, MPI_DOUBLE};
  displacements[0] = offsetof(per_object_t, player_id);
  displacements[1] = offsetof(per_object_t, uper);
  displacements[2] = offsetof(per_object_t, per);

  MPI_Type_create_struct(3, block_lengths, displacements, types,
                         &mpi_per_object);
  MPI_Type_commit(&mpi_per_object);

  return mpi_per_object;
}

/**
 * Create a MPI_Datatype definition for game object
 *
 * @return the MPI_Datatype for a game_t
 */
MPI_Datatype create_game_object() {
  MPI_Datatype mpi_game;
  int block_lengths[18] = {1, 1, 1, 4, 1, 1, 1, 1, 1,
                           1, 1, 1, 1, 1, 1, 1, 1, 1};
  MPI_Aint displacements[18];
  MPI_Datatype types[18] = {MPI_INT, MPI_INT, MPI_INT, MPI_CHAR, MPI_INT,
                            MPI_INT, MPI_INT, MPI_INT, MPI_INT,  MPI_INT,
                            MPI_INT, MPI_INT, MPI_INT, MPI_INT,  MPI_FLOAT,
                            MPI_INT, MPI_INT, MPI_INT};
  displacements[0] = offsetof(game_t, player_id);
  displacements[1] = offsetof(game_t, game_id);
  displacements[2] = offsetof(game_t, season);
  displacements[3] = offsetof(game_t, team_abbreviation);
  displacements[4] = offsetof(game_t, pts);
  displacements[5] = offsetof(game_t, reb);
  displacements[6] = offsetof(game_t, ast);
  displacements[7] = offsetof(game_t, stl);
  displacements[8] = offsetof(game_t, blk);
  displacements[9] = offsetof(game_t, turnover);
  displacements[10] = offsetof(game_t, fgm);
  displacements[11] = offsetof(game_t, fga);
  displacements[12] = offsetof(game_t, ftm);
  displacements[13] = offsetof(game_t, fta);
  displacements[14] = offsetof(game_t, min);
  displacements[15] = offsetof(game_t, pf);
  displacements[16] = offsetof(game_t, oreb);
  displacements[17] = offsetof(game_t, dreb);

  MPI_Type_create_struct(18, block_lengths, displacements, types, &mpi_game);
  MPI_Type_commit(&mpi_game);

  return mpi_game;
}

/**
 * Create a MPI_Datatype definition for a player agg object
 *
 * @param mpi_stat_agg_obj MPI_Datatype for stat_agg_t object
 * @return the MPI_Datatype for a player_and_agg_t
 */
MPI_Datatype create_player_stat_and_agg_object(MPI_Datatype mpi_stat_agg_obj) {
  MPI_Datatype mpi_player_stat_and_agg_obj;
  int block_lengths[2] = {1, 1};
  MPI_Aint displacements[2];
  displacements[0] = offsetof(player_and_agg_t, player_id);
  displacements[1] = offsetof(player_and_agg_t, player_agg_stats);
  MPI_Datatype types[2] = {MPI_INT, mpi_stat_agg_obj};

  MPI_Type_create_struct(2, block_lengths, displacements, types,
                         &mpi_player_stat_and_agg_obj);
  MPI_Type_commit(&mpi_player_stat_and_agg_obj);

  return mpi_player_stat_and_agg_obj;
}

/**
 * Send a stat_agg with MPI
 *
 * @param data data to send
 * @param dest_rank rank to send to
 * @param mpi_struct MPI_Datatype for stat_agg_t
 */
void send_stat_agg(stat_agg_t *data, int dest_rank, MPI_Datatype mpi_struct) {
  MPI_Send(data, 1, mpi_struct, dest_rank, 0, MPI_COMM_WORLD);
}

/**
 * Receive a stat agg with mpi
 *
 * @param data pointer to store data
 * @param source_rank rank to receive from
 * @param mpi_struct MPI_Datatype for stat_agg_t
 */
void recv_stat_agg(stat_agg_t *data, int source_rank, MPI_Datatype mpi_struct) {
  MPI_Recv(data, 1, mpi_struct, source_rank, 0, MPI_COMM_WORLD,
           MPI_STATUS_IGNORE);
}

/**
 * Send a player per with MPI
 *
 * @param data data to send
 * @param dest_rank rank to send to
 * @param mpi_struct MPI_Datatype for per_object_t
 */
void send_player_per(per_object_t *data, int dest_rank,
                     MPI_Datatype mpi_struct) {
  MPI_Send(data, 1, mpi_struct, dest_rank, 0, MPI_COMM_WORLD);
}

/**
 * Receive a per_object with MPI
 *
 * @param data pointer to where to store per_object_t received
 * @param source_rank rank to receive from
 * @param mpi_struct MPI_Datatype for per_object_t
 */
void recv_player_per(per_object_t *data, int source_rank,
                     MPI_Datatype mpi_struct) {
  MPI_Recv(data, 1, mpi_struct, source_rank, 0, MPI_COMM_WORLD,
           MPI_STATUS_IGNORE);
}
