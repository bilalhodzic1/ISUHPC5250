#include "node.h"
/**
 * @brief Pops one node from the stack. Returns the PO stored at the top node
 * and removes it from the stack
 *
 * @param  top A reference to the current top node of the stack
 * @return The purchase order which was held by the top node of the stack
 */
purchase_order_t pop(node_t **top) {
  purchase_order_t po_from_top = (*top)->po;
  (*top) = (*top)->next;
  return po_from_top;
}
