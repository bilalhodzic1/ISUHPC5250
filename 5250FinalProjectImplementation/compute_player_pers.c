#include "hashmap.h"
#include "per_engine.h"

double get_unadjusted_per(stat_agg_t player_aggs){
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
    double player_total = scaled_fgm + scaled_ftm + scaled_oreb + scaled_dreb + scaled_ast + scaled_stl + scaled_blk - scaled_fga - scaled_fta - scaled_to - scaled_pf;
    if(player_aggs.mins_agg == 0){
        return 0;
    }else{
        return player_total / player_aggs.mins_agg;
    }
}

per_object_t* compute_player_pers(HashItem** player_agg_hashmap, int* num_players_ptr){
    per_object_t* player_pers = NULL;
    int num_players = 0;
    double u_per_sum = 0;
    HashItem *current_item, *tmp;
    HASH_ITER(hh, *player_agg_hashmap, current_item, tmp) {
        player_pers = realloc(player_pers, (num_players + 1) * sizeof(per_object_t));
        stat_agg_t player_aggs = *current_item->value;
        double u_per = get_unadjusted_per(player_aggs);
        //printf("%lf\n", u_per);
        per_object_t player_per;
        player_per.player_id = current_item->key;
        player_per.uper = u_per;
        player_pers[num_players] = player_per;
        num_players++;
        u_per_sum += u_per;
    }
    double league_average_uper = u_per_sum / num_players;
    int i;
    for(i = 0; i < num_players; i++){
        player_pers[i].per = player_pers[i].uper * (15.0 / league_average_uper);
    }
    *num_players_ptr = num_players;
    return player_pers;
}
