#include "node.h"

int main(int argc, char *argv[]) {
  display_options();
  purchase_order_t test_po = create_new_po();
  node_t *top;
  push(&top, test_po);
  purchase_order_t from_the_stack_po = pop(&top);
  printf("PO NUm: %d\n PO amount: %lf\n PO Descr: %s\n",
         from_the_stack_po.po_number, from_the_stack_po.po_amount,
         from_the_stack_po.po_description);
  return 0;
}
