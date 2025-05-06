#ifndef __PERENGINE__
#define __PERENGINE__
#include "csvutils.h"
#include "hashmap.h"
#include "mpi.h"
typedef struct per_object {
  int player_id;
  double per;
  double uper;
} per_object_t;
typedef struct player_and_agg {
  int player_id;
  stat_agg_t player_agg_stats;
} player_and_agg_t;

HashItem *compute_season_aggregates(game_t *games, int num_games);
double get_unadjusted_per(stat_agg_t player_aggs);
per_object_t *compute_player_pers(HashItem **player_agg_hashmap,
                                  int *num_players_ptr);
MPI_Datatype create_stat_object();
MPI_Datatype create_player_per_object();
MPI_Datatype create_game_object();
MPI_Datatype create_player_stat_and_agg_object(MPI_Datatype mpi_stat_agg_obj);
void send_stat_agg(stat_agg_t *data, int dest_rank, MPI_Datatype mpi_struct);
void recv_stat_agg(stat_agg_t *data, int source_rank, MPI_Datatype mpi_struct);
void send_player_per(per_object_t *data, int dest_rank,
                     MPI_Datatype mpi_struct);
void recv_player_per(per_object_t *data, int source_rank,
                     MPI_Datatype mpi_struct);
void broadcast_game_count(int *num_games);
void compute_sendcounts_and_displacements(int *sendcounts,
                                          int *process_displacements,
                                          int num_item, int comm_sz);
void scatter_game_array(int my_rank, int *sendcounts,
                        int *process_displacements, MPI_Datatype mpi_game_obj,
                        game_t *local_games, int local_count, game_t *games);
player_and_agg_t *compute_local_player_agg_array(game_t *local_games,
                                                 int local_count,
                                                 int *player_count);
per_object_t *
compute_player_upers_array(player_and_agg_t *player_and_aggs_array,
                           int num_players, double *total_uper);
#endif
