#include "csvutils.h"
/**
* Splits a string on a delmitter
*
* @param str a string to be split
* @param delimiter a string to be used as a delimiter
* @param num_tokens an int pointer to be set to num of strings in array
* @return an array of strings containing the split values
*/
char** split_string(char* str, char* delimiter, int* num_tokens){
    char *token;
    char *rest = str;
    char** tokens = malloc(sizeof(char*) * 19);
    int index = 0;
    while ((token = strsep(&rest, delimiter)) != NULL) {
        tokens[index] = token;
        index++;
    }
    *num_tokens = 19;
    return tokens;
}
