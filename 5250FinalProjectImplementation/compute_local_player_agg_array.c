#include "per_engine.h"
/**
 * Computes local player aggregate array from a set of games
 *
 * @param local_games an array of games to compute aggregates from
 * @param local_count the number of games in the array
 * @param player_count pointer to int where the amount of players will be stored
 * @return array of player_and_agg_t objects which holds player aggregates for
 * the whole set of games
 */
player_and_agg_t *compute_local_player_agg_array(game_t *local_games,
                                                 int local_count,
                                                 int *player_count) {
  // Initialize empty return array
  player_and_agg_t *local_player_agg_array = NULL;
  // Compute season aggregate hashmaps
  HashItem *local_player_agg_map =
      compute_season_aggregates(local_games, local_count);
  // Set up for hashmap iteration
  int i = 0;
  *player_count = 0;
  HashItem *current_item, *tmp;

  HASH_ITER(hh, local_player_agg_map, current_item, tmp) {
    // For each item in hashmap make a copy to local array for return
    local_player_agg_array =
        realloc(local_player_agg_array, (i + 1) * sizeof(player_and_agg_t));
    local_player_agg_array[i].player_agg_stats = *(current_item->value);
    local_player_agg_array[i].player_id = current_item->key;
    // Increment array index and player count
    i++;
    (*player_count)++;
  }
  // Return array of player aggs
  return local_player_agg_array;
}
