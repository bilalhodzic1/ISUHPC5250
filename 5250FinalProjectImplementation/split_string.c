#include "csvutils.h"

char** split_string(char* str, char* delimiter, int* num_tokens){
    char *token;
    char *rest = str;
    char** tokens = malloc(sizeof(char*) * 16);
    int index = 0;
    while ((token = strsep(&rest, delimiter)) != NULL) {
        tokens[index] = token;
        index++;
    }
    *num_tokens = 16;
    return tokens;
}
