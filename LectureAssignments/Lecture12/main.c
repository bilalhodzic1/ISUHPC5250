#include "node.h"

int main(int argc, char *argv[]) {

  printf("This program will keep track of purchase orders.\n Purchase orders "
         "are handled last in first out for some reason at this company");
  node_t *top = NULL;
  int option_selected = 0;
  while (option_selected != 6) {
    execute_option(option_selected, &top);
    option_selected = query_option();
  }
  return 0;
}
