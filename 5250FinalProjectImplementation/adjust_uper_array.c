#include "per_engine.h"
/**
 * Adjusts all unadjusted PERS in a per_object_t array
 *
 * @param local_player_final_count number of players in the array
 * @param local_uper_array array of per_object_t contaning players with thier
 * upers
 * @param global_average_uper the average uper for adjusting
 */
void adjust_uper_array(int local_player_final_count,
                       per_object_t *local_uper_array,
                       double global_average_uper) {
  // Loop through all players and appl standard adjustment
  for (int i = 0; i < local_player_final_count; i++) {
    local_uper_array[i].per =
        local_uper_array[i].uper * (15.0 / global_average_uper);
  }
}
