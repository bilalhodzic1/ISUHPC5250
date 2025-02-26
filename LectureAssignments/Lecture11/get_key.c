#include "node.h"

char get_key() {
  printf("Enter character to find in list (0 to quit): \n");
  char search_char;
  scanf(" %c", &search_char);
  return search_char;
}
