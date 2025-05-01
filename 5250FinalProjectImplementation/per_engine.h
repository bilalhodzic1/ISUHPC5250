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

HashItem *compute_season_aggregates(game_t *games, int num_games);
per_object_t *compute_player_pers(HashItem **player_agg_hashmap,
                                  int *num_players_ptr);
MPI_Datatype create_stat_object();
MPI_Datatype create_player_per_object();
MPI_Datatype create_game_object();
void send_stat_agg(stat_agg_t *data, int dest_rank, MPI_Datatype mpi_struct);
void recv_stat_agg(stat_agg_t *data, int source_rank, MPI_Datatype mpi_struct);
void send_player_per(per_object_t *data, int dest_rank,
                     MPI_Datatype mpi_struct);
void recv_player_per(per_object_t *data, int source_rank,
                     MPI_Datatype mpi_struct);
#endif
