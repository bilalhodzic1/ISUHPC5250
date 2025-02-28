#include "node.h"
/**
 * @brief Pops one node from the stack. Returns the PO stored at the top node
 * and removes it from the stack
 *
 * @param  top A reference to the current top node of the stack
 * @return The purchase order which was held by the top node of the stack
 */
node_t *pop(node_t **top) {
  node_t *po_from_top = (node_t *)malloc(sizeof(node_t));
  node_t *temp = *top;
  po_from_top->po = temp->po;
  (*top) = (*top)->next;
  free(temp);
  return po_from_top;
}
