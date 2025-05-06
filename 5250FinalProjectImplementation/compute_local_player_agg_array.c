#include "per_engine.h"

stat_agg_t *compute_local_player_agg_array(game_t *local_games, int local_count,
                                           int *player_count) {
  stat_agg_t *local_player_agg_array = NULL;
  HashItem *local_player_agg_map =
      compute_season_aggregates(local_games, local_count);
  int i = 0;
  *player_count = 0;
  HashItem *current_item, *tmp;

  HASH_ITER(hh, local_player_agg_map, current_item, tmp) {
    local_player_agg_array =
        realloc(local_player_agg_array, (i + 1) * sizeof(stat_agg_t));
    local_player_agg_array[i] = *(current_item->value);
    i++;
    (*player_count)++;
  }
  return local_player_agg_array;
}
