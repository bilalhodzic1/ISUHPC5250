#include "per_engine.h"

/**
 * Joins player agg object array into one hashmap
 *
 * @param actual_player_count pointer to an integer where the actual total
 * player count will be stored
 * @param total_players the amount of player_agg objects in the array
 * @param global_players_array array of all player and aggs from all processes
 * @param complete_player_agg_array pointer to array where we will keep all the
 * complete aggregate results
 */
void join_player_aggs_to_map(int *actual_player_count, int total_players,
                             player_and_agg_t *global_players_array,
                             player_and_agg_t **complete_player_agg_array) {
  // Set acutal count to 0 initially
  *actual_player_count = 0;
  // Setup hashmap
  HashItem *complete_player_agg_map = NULL;
  // Loop thorugh global_players_array
  for (int i = 0; i < total_players; i++) {
    // Check if item exists in map already
    HashItem *item =
        find(global_players_array[i].player_id, &complete_player_agg_map);
    // If item is found aggreagte aggs
    if (item) {
      stat_agg_t *existing_stat_agg = item->value;
      stat_agg_t new_stat_agg = global_players_array[i].player_agg_stats;
      existing_stat_agg->fgm_agg += new_stat_agg.fgm_agg;
      existing_stat_agg->ftm_agg += new_stat_agg.ftm_agg;
      existing_stat_agg->oreb_agg += new_stat_agg.oreb_agg;
      existing_stat_agg->dreb_agg += new_stat_agg.dreb_agg;
      existing_stat_agg->ast_agg += new_stat_agg.ast_agg;
      existing_stat_agg->stl_agg += new_stat_agg.stl_agg;
      existing_stat_agg->blk_agg += new_stat_agg.blk_agg;
      existing_stat_agg->fga_agg += new_stat_agg.fga_agg;
      existing_stat_agg->fta_agg += new_stat_agg.fta_agg;
      existing_stat_agg->to_agg += new_stat_agg.to_agg;
      existing_stat_agg->pf_agg += new_stat_agg.pf_agg;
      existing_stat_agg->mins_agg += new_stat_agg.mins_agg;
    } else {
      // If not found increment player count and add to map
      (*actual_player_count)++;
      insert(global_players_array[i].player_id,
             &(global_players_array[i].player_agg_stats),
             &complete_player_agg_map);
    }
  }
  // Setup loop iterating items
  HashItem *current_item, *tmp;
  // Initialize player_agg_array
  *complete_player_agg_array =
      malloc(sizeof(player_and_agg_t) * (*actual_player_count));
  // Iterate through hashmap and move to array
  int i = 0;
  HASH_ITER(hh, complete_player_agg_map, current_item, tmp) {
    (*complete_player_agg_array)[i].player_agg_stats = *(current_item->value);
    (*complete_player_agg_array)[i].player_id = current_item->key;
    i++;
  }
}
