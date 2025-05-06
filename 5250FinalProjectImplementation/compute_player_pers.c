#include "hashmap.h"
#include "per_engine.h"

/**
 * Computes PERs for all players in a season
 *
 * @param player_agg_hashmap a hashmap containing player ids and aggregate
 * totals
 * @param num_players_ptr a pointer where num_players will be stored
 * @return an array of per_object_t which contains player PER info
 */
per_object_t *compute_player_pers(HashItem **player_agg_hashmap,
                                  int *num_players_ptr) {
  // Declare empty array, counter, and sum object
  per_object_t *player_pers = NULL;
  int num_players = 0;
  double u_per_sum = 0;
  // Declare uthash iteration objects
  HashItem *current_item, *tmp;
  // Iterate through hashmap
  HASH_ITER(hh, *player_agg_hashmap, current_item, tmp) {
    // Realloc to grow array based on player count
    player_pers =
        realloc(player_pers, (num_players + 1) * sizeof(per_object_t));
    // Fetch stat agg object from hashmap
    stat_agg_t player_aggs = *current_item->value;
    // Cacluate uper
    double u_per = get_unadjusted_per(player_aggs);
    // Initialize and set per_object fields
    per_object_t player_per;
    player_per.player_id = current_item->key;
    player_per.uper = u_per;
    // Store in array and adjust counter and sums
    player_pers[num_players] = player_per;
    num_players++;
    u_per_sum += u_per;
  }
  // Get league average
  double league_average_uper = u_per_sum / num_players;
  // Apply adjustment to PERS
  int i;
  for (i = 0; i < num_players; i++) {
    player_pers[i].per = player_pers[i].uper * (15.0 / league_average_uper);
  }
  // Return array and set num players
  *num_players_ptr = num_players;
  return player_pers;
}
