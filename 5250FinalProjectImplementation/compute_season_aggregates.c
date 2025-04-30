#include "csvutils.h"
#include "hashmap.h"
#include "per_engine.h"

void aggregate_stats(stat_agg_t *prev, game_t game){
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
}

HashItem* compute_season_aggregates(game_t* games, int num_games){
    HashItem* hashmap = NULL;
    int i;
    for (i = 0; i < num_games; i++){

    }
    return hashmap;
}
