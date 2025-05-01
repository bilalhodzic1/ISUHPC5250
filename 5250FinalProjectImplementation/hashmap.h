#ifndef __HASHMAP__
#define __HASHMAP__
#include "uthash.h"
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
typedef struct {
  int key;
  stat_agg_t *value;
  UT_hash_handle hh;
} HashItem;
void insert(int key, stat_agg_t *value, HashItem **hashmap);
HashItem *find(int key, HashItem **hashmap);
void delete(int key, HashItem **hashmap);
void cleanup(HashItem **hashmap);
#endif
