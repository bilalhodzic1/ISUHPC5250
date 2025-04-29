/*
OUTLINE:

READ CSV into data rows for processing
    CSV is ordered by season/player
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

int main(int argc, char* argv[]){
    int num_tokens;
    char str[] = "375,Michael Porter Jr.,1037593,2023,DEN,12,12,2,2,0,0,5,13,0,0,30.0";
    char delmitter[] = ",";
    char** string_arr = split_string(str, delmitter,&num_tokens);
    int i;
    for(i = 0; i < 16; i++){
        printf("String %d: %s\n", i, string_arr[i]);
    }
    return 0;
}
