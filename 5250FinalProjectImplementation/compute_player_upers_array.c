#include "per_engine.h"
per_object_t *
compute_player_upers_array(player_and_agg_t *player_and_aggs_array,
                           int num_players, int *total_uper) {
  per_object_t *final_upers =
      (per_object_t *)malloc(sizeof(per_object_t) * num_players);
  *total_uper = 0;
  int i;
  for (i = 0; i < num_players; i++) {
    stat_agg_t player_stat_agg = player_and_aggs_array[i].player_agg_stats;
    double uper = get_unadjusted_per(player_stat_agg);
    *total_uper += uper;
    per_object_t player_per;
    player_per.player_id = player_and_aggs_array[i].player_id;
    player_per.uper = uper;
    final_upers[i] = player_per;
  }
  return final_upers;
}
