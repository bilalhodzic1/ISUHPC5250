#include "csvutils.h"
/**
 * Splits a string on a delmitter
 *
 * @param str a string to be split
 * @param delimiter a string to be used as a delimiter
 * @param num_tokens an int pointer to be set to num of strings in array
 * @return an array of strings containing the split values
 */
char **split_string(char *str, char *delimiter, int *num_tokens) {
  char *copy = strdup(str); // Make a modifiable copy of the string
  if (!copy)
    return NULL;

  char **tokens = malloc(sizeof(char *) * 19); // Adjust if needed
  int index = 0;

  char *token = strtok(copy, delimiter);
  while (token != NULL && index < 19) {
    tokens[index++] = token;
    token = strtok(NULL, delimiter);
  }

  *num_tokens = index;
  return tokens;
}
