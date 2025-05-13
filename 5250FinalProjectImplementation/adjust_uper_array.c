#include "per_engine.h"
void adjust_uper_array(int local_player_final_count,
                       per_object_t *local_uper_array,
                       double global_average_uper) {
  for (int i = 0; i < local_player_final_count; i++) {
    local_uper_array[i].per =
        local_uper_array[i].uper * (15.0 / global_average_uper);
  }
}
