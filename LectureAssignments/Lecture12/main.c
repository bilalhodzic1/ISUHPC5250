#include "node.h"

int main(int argc, char *argv[]) {
  display_options();
  node_t *top;
  int i;
  for (i = 0; i < 5; i++) {
    purchase_order_t test_po = create_new_po();
    push(&top, test_po);
    purchase_order_t from_the_stack_po = peek(&top);
    printf("PO NUm: %d\n PO amount: %lf\n PO Descr: %s\n",
           from_the_stack_po.po_number, from_the_stack_po.po_amount,
           from_the_stack_po.po_description);
    printf("Stack size : %d\n", get_stack_size(&top));
  }
  pop(&top);
  pop(&top);
  pop(&top);
  printf("Stack size : %d\n", get_stack_size(&top));

  return 0;
}
