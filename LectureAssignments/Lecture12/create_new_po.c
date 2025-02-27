#include "node.h"
#include <stdio.h>

/**
 * @brief Gets inputs from the user to create a new purchase_order_t.
 *
 * @return A new purchase_order_t created from the user inputs
 */
purchase_order_t create_new_po() {
  purchase_order_t new_po;
  printf("Enter a PO number: \n");
  scanf("%d\n", &new_po.po_number);
  printf("Enter the total cost of the PO: \n");
  scanf("%lf\n", &new_po.po_amount);
  printf("Enter a brief description of the PO:\n");
  fgets(new_po.po_description, sizeof(new_po.po_description), stdin);
  return new_po;
}
