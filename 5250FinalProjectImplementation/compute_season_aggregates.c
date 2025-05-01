#include "csvutils.h"
#include "hashmap.h"
#include "per_engine.h"
/**
 * Adds a current games stats to a stat aggregate object
 * @param prev a pointer to the previous stat_agg object
 * @param game a game containing some stats for a player
 */
void aggregate_stats(stat_agg_t *prev, game_t game) {
  // Add up the stats
  prev->fgm_agg += game.fgm;
  prev->ftm_agg += game.ftm;
  prev->oreb_agg += game.oreb;
  prev->dreb_agg += game.dreb;
  prev->ast_agg += game.ast;
  prev->stl_agg += game.stl;
  prev->blk_agg += game.blk;
  prev->fga_agg += game.fga;
  prev->fta_agg += game.fta;
  prev->to_agg += game.turnover;
  prev->pf_agg += game.pf;
  prev->mins_agg += game.min;
}
/**
 * Initializes a stat aggregate object with the stats from a game
 * @param new a pointer to the new stat_agg object
 * @param game a game containing some stats for a player
 */
void initialize_stat_obj(stat_agg_t *new, game_t game, int player_id) {
  // Set intial values of the stats
  new->fgm_agg = game.fgm;
  new->ftm_agg = game.ftm;
  new->oreb_agg = game.oreb;
  new->dreb_agg = game.dreb;
  new->ast_agg = game.ast;
  new->stl_agg = game.stl;
  new->blk_agg = game.blk;
  new->fga_agg = game.fga;
  new->fta_agg = game.fta;
  new->to_agg = game.turnover;
  new->pf_agg = game.pf;
  new->mins_agg = game.min;
  new->player_id = player_id;
}
/**
 * Computes aggregates per player for a season of games
 *
 * @param games an array of games in a season per player
 * @param num_games the number of game objects in that seasons
 * @return a hashmap containing the aggregated stats for each player
 */
HashItem *compute_season_aggregates(game_t *games, int num_games) {
  // Declare hashmap to NULL
  HashItem *hashmap = NULL;
  // Loop through games
  int i;
  for (i = 0; i < num_games; i++) {
    // For each game attempt to find if player already has stats
    game_t curr_game = games[i];
    HashItem *item = find(curr_game.player_id, &hashmap);
    // Check if player was found
    if (item) {
      // If found aggregate to pointer
      aggregate_stats(item->value, curr_game);
    } else {
      // If not found create new stat pointer and intitalize
      stat_agg_t *new_stats = (stat_agg_t *)malloc(sizeof(stat_agg_t));
      initialize_stat_obj(new_stats, curr_game, curr_game.player_id);
      // Insert player to hashmap
      insert(curr_game.player_id, new_stats, &hashmap);
    }
  }
  return hashmap;
}
