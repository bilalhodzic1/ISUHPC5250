#include "node.h"

int main(int argc, char *argv[]) {
  node_t *top = NULL;
  int option_selected = 0;
  while (option_selected != 6) {
    execute_option(option_selected, &top);
    option_selected = query_option();
  }
  return 0;
}
