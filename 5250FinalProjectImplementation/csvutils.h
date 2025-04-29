#ifndef __CSVUTIL__
#define __CSVUTIL__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct game{
    int player_id;
    int game_id;
    int season;
    char* team_abbreviation;
    int pts;
    int reb;
    int ast;
    int stl;
    int blk;
    int turnover;
    int fgm;
    int fga;
    int ftm;
    int fta;
    float min;
} game_t;

game_t* read_games(FILE* file, int* num_games);
void free_games(game_t* games, int num_games);

char** split_string(char* str, char* delimiter, int* num_tokens);

#endif
