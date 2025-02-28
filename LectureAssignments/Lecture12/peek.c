#include "node.h"
/**
 * @brief Returns the top node of the stack without removing it
 * from the stack
 *
 * @param  top A reference to the top node of the stack
 * @return A node_t instance contained at the current top
 */
node_t *peek(node_t **top) { return (*top); }
