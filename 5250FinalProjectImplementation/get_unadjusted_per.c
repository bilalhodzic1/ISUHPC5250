#include "per_engine.h"

/**
 * Computes unadjusted PER based on simplified calculation for a player
 * aggregate
 *
 * @param player_aggs a stat_agg_t containing a players aggregates for a season
 * @return the unadjusted per for the plater
 */
double get_unadjusted_per(stat_agg_t player_aggs) {
  // Compute scaling for all aggregate stats. Scalings based on approximate
  // values for simplicity
  double scaled_fgm = player_aggs.fgm_agg * 85.91;
  double scaled_ftm = player_aggs.ftm_agg * 46.845;
  double scaled_oreb = player_aggs.oreb_agg * 39.19;
  double scaled_dreb = player_aggs.dreb_agg * 21.575;
  double scaled_ast = player_aggs.ast_agg * 34.677;
  double scaled_stl = player_aggs.stl_agg * 53.897;
  double scaled_blk = player_aggs.blk_agg * 39.19;
  double scaled_fga = player_aggs.fga_agg * 39.19;
  double scaled_fta = player_aggs.fta_agg * 20.091;
  double scaled_to = player_aggs.to_agg * 53.897;
  double scaled_pf = player_aggs.pf_agg * 17.174;
  // Compute weighted total
  double player_total = scaled_fgm + scaled_ftm + scaled_oreb + scaled_dreb +
                        scaled_ast + scaled_stl + scaled_blk - scaled_fga -
                        scaled_fta - scaled_to - scaled_pf;
  // If minutes are 0 then we avoid divide by 0
  if (player_aggs.mins_agg == 0) {
    return 0;
  } else {
    // Return uper
    return player_total / player_aggs.mins_agg;
  }
}
