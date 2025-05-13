#include "per_engine.h"
/**
 * Computes an array of per_object_t filled with players and thier unadjusted
 * PERs for a set of aggregates
 *
 * @param player_and_aggs_array an array containing player aggregates
 * @param num_players the number of players in the array
 * @param total_uper pointer to double where total uper of the array is stored
 * @return array of per_object_t containing players and thier unadjusted PERS
 */
per_object_t *
compute_player_upers_array(player_and_agg_t *player_and_aggs_array,
                           int num_players, double *total_uper) {
  // If there is nothing return NULL pointer
  if (num_players == 0) {
    return NULL;
  }
  // Set size of return array to number of players
  per_object_t *final_upers =
      (per_object_t *)malloc(sizeof(per_object_t) * num_players);
  // Initialize loop variables
  *total_uper = 0;
  int i;
  // Loop through all players in player agg array
  for (i = 0; i < num_players; i++) {
    // Get unadjusted PER based on player aggs
    stat_agg_t player_stat_agg = player_and_aggs_array[i].player_agg_stats;
    double uper = get_unadjusted_per(player_stat_agg);
    // Sum uper total
    *total_uper += uper;
    // Create and store player_per_t object to array
    per_object_t player_per;
    player_per.player_id = player_and_aggs_array[i].player_id;
    player_per.uper = uper;
    final_upers[i] = player_per;
  }
  // Return final array of player_per_t object
  return final_upers;
}
