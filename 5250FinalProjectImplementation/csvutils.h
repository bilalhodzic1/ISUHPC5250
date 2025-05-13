#ifndef __CSVUTIL__
#define __CSVUTIL__
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#pragma pack(push, 1)
typedef struct game {
  int player_id;
  int game_id;
  int season;
  char team_abbreviation[4];
  int pts;
  int reb;
  int ast;
  int stl;
  int blk;
  int turnover;
  int fgm;
  int fga;
  int ftm;
  int fta;
  float min;
  int pf;
  int oreb;
  int dreb;
} game_t;
#pragma pack(pop)
game_t *read_games(FILE *file, int *num_games);

char **split_string(char *str, char *delimiter, int *num_tokens);

void get_num_games(size_t record_size, int *num_games);

#endif
