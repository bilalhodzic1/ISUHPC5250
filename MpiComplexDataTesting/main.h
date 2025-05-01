#ifndef __MAIN_H__
#define __MAIN_H__
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct stat_agg {
  int fgm_agg;
  int ftm_agg;
  int oreb_agg;
  int dreb_agg;
  int ast_agg;
  int stl_agg;
  int blk_agg;
  int fga_agg;
  int fta_agg;
  int to_agg;
  int pf_agg;
  float mins_agg;
  int player_id;
} stat_agg_t;
typedef struct per_object {
  int player_id;
  double per;
  double uper;
} per_object_t;

MPI_Datatype create_stat_object();
MPI_Datatype create_player_per_object();
void send_stat_agg(stat_agg_t *data, int dest_rank, MPI_Datatype mpi_struct);
void recv_stat_agg(stat_agg_t *data, int source_rank, MPI_Datatype mpi_struct);
void send_player_per(per_object_t *data, int dest_rank,
                     MPI_Datatype mpi_struct);
void recv_player_per(per_object_t *data, int source_rank,
                     MPI_Datatype mpi_struct);
#endif
