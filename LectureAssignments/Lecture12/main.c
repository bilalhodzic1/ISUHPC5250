#include "node.h"

int main(int argc, char *argv[]) {
  display_options();
  purchase_order_t test_po = create_new_po();
  printf("Purchase order details\n PO Num: %d\n PO amount %lf\n PO description "
         "%s\n",
         test_po.po_number, test_po.po_amount, test_po.po_description);
  return 0;
}
