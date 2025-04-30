/*
OUTLINE:

READ CSV into data rows for processing
    CSV is ordered by season/player

Compute game PER using simplified formula
    Maybe I will extend this im not sure
Get game_id player_id and PER from this

Compute in parallel the UPER for a player in each season
    UPER is composed of many aggregate stats
    Should be possible to compute these in parallel (About 2 million total data points)
    How to do this with MPI to maximize parallelization? Is this even a good idea
Wait for all seasons to be computed
Separate by season to get num over 15 UPER per season
Determin scaling factor
Go through each UPER and multiple the scalaing factor
*/
#include "csvutils.h"
#include "hashmap.h"
#include "per_engine.h"
int main(int argc, char* argv[]){
    //Serial implementation:
    FILE* file = fopen("1.csv", "r");
    int num_games;
    game_t* games = read_games(file, &num_games);
    HashItem* player_agg_map = compute_season_aggregates(games, num_games);
    int num_players;
    per_object_t* player_pers = compute_player_pers(&player_agg_map, &num_players);
    int i;
    for(i = 0; i < num_players; i++){
        if(player_pers[i].player_id == 237){
            printf("Player ID: %d, Player PER: %lf\n", player_pers[i].player_id, player_pers[i].per);
        }
    }
    return 0;
}
