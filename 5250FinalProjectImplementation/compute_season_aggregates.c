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
void initialize_stat_obj(stat_agg_t *new, game_t game){
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
}

HashItem* compute_season_aggregates(game_t* games, int num_games){
    HashItem* hashmap = NULL;
    int i;
    for (i = 0; i < num_games; i++){
        game_t curr_game = games[i];
        HashItem* item = find(curr_game.player_id, &hashmap);
        if(item){
            aggregate_stats(item->value, curr_game);
        }else{
            stat_agg_t* new_stats = (stat_agg_t*)malloc(sizeof(stat_agg_t));
            initialize_stat_obj(new_stats, curr_game);
            insert(curr_game.player_id, new_stats,&hashmap);
        }
    }
    return hashmap;
}
