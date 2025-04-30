#ifndef __PERENGINE__
#define __PERENGINE__
#include "hashmap.h"
#include "csvutils.h"
typedef struct per_object{
    int player_id;
    double per;
    double uper;
}per_object_t;

HashItem* compute_season_aggregates(game_t* games, int num_games);
per_object_t* compute_player_pers(HashItem** player_agg_hashmap, int* num_players_ptr);

#endif
