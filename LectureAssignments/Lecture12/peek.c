#include "node.h"
/**
 * @brief Returns the data from the top node of the stack without removing it
 * from the stack
 *
 * @param  top A reference to the top node of the stack
 * @return A purchase_order_t instance contained at the current top
 */
purchase_order_t peek(node_t **top) { return (*top)->po; }
