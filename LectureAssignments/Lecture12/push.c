#include "node.h"
/**
 * @brief  Pushes a new node to the top of the stack.
 *
 * @param  top: The current stack top node.
 * @param  new_po: a new purchase order object to be added to the created node
 * @return no return function is void
 */
void push(node_t **top, purchase_order_t new_po) {
  if (*top == NULL) {
    *top = (node_t *)malloc(sizeof(node_t));
    (*top)->next = NULL;
    (*top)->po = new_po;
  } else {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->po = new_po;
    new_node->next = (*top);
    *top = new_node;
  }
}
