#include "node.h"

int main(int argc, char *argv[]) {
  display_options();
  node_t *top = NULL;
  int i;
  for (i = 0; i < 2; i++) {
    purchase_order_t test_po = create_new_po();
    push(&top, test_po);
  }
  display_stack(&top);
  return 0;
}
