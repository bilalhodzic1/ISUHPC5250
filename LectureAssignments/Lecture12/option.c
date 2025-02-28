#include "node.h"
/**
 * @brief gets an input from the user to use as an option
 *
 * @return the option entered by the user as an int
 */
int query_option() {
  int option = 0;
  printf("Enter option: \n");
  scanf("%d", &option);
  return option;
}
/**
 * @brief executes code based on an option passed in by the user
 *
 * @param  option the option the user entered. A number 0-6
 * @param  top a reference to the node at the top of the stack
 * @return nothing, the function is void
 */
void execute_option(int option, node_t **top) {
  if (option < 0 || option > 6) {
    return;
  }
  purchase_order_t new_po;
  node_t *popped_po;
  int size_of_stack = get_stack_size(top);
  switch (option) {
  case 0:
    display_options();
    break;
  case 1:
    new_po = create_new_po();
    push(top, new_po);
    break;
  case 2:
    if (size_of_stack == 0) {
      printf("Nothing in stack\n");
      break;
    }
    popped_po = pop(top);
    printf("Purchase order %d has been removed!\n", popped_po->po.po_number);
    break;
  case 3:
    if (size_of_stack == 0) {
      printf("Nothing in stack\n");
      break;
    }
    popped_po = peek(top);
    printf("Purchase order %d is next for processing!\n",
           popped_po->po.po_number);
    break;
  case 4:
    display_stack(top);
    break;
  case 5:
    size_of_stack = get_stack_size(top);
    printf("The stack currently holds %d purchase orders\n", size_of_stack);
    break;
  case 6:
    delete_stack(top);
    break;
  }
}
