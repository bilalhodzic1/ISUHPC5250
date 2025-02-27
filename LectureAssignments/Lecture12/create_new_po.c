#include "node.h"
#include <stdio.h>

/**
 * @brief Flushes new lines from the input to get fgets to work properly.
 *
 * @return nothing, function is void
 */
void flush_new_line_chars() {
  while (getchar() != '\n')
    ;
}

/**
 * @brief Gets inputs from the user to create a new purchase_order_t.
 *
 * @return A new purchase_order_t created from the user inputs
 */
purchase_order_t create_new_po() {
  purchase_order_t new_po;
  printf("Enter a PO number: \n");
  scanf("%d", &new_po.po_number);
  printf("Enter the total cost of the PO: \n");
  scanf("%lf", &new_po.po_amount);
  flush_new_line_chars();
  printf("Enter a brief description of the PO (Max of %d characters!):\n",
         (int)sizeof(new_po.po_description));
  fgets(new_po.po_description, sizeof(new_po.po_description), stdin);
  return new_po;
}
