#include "node.h"

int query_option() {
  int option = 0;
  printf("Enter option: \n");
  scanf("%d", &option);
  return option;
}

void execute_option(int option, node_t **top) {
  if (option < 0 || option > 6) {
    return;
  }
  purchase_order_t new_po;
  purchase_order_t popped_po;
  int size_of_stack = 0;
  switch (option) {
  case 0:
    display_options();
    break;
  case 1:
    new_po = create_new_po();
    push(top, new_po);
    break;
  case 2:
    popped_po = pop(top);
    printf("Purchase order %d has been removed!\n", popped_po.po_number);
    break;
  case 3:
    popped_po = peek(top);
    printf("Purchase order %d is next for processing!\n", popped_po.po_number);
    break;
  case 4:
    display_stack(top);
    break;
  case 5:
    size_of_stack = get_stack_size(top);
    printf("The stack currently holds %d purchase orders\n", size_of_stack);
    break;
  case 6:
    break;
  }
}
