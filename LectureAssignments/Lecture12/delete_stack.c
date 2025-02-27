#include "node.h"

/**
 * @brief Deletes the entire stack. frees all the memory allocated for it
 *
 * @param  top A reference to the top node of the stack
 * @return nothing, function is void
 */
void delete_stack(node_t **top) {
  node_t *tracer;
  while (*top != NULL) {
    tracer = *top;
    *top = (*top)->next;
    free(tracer);
  }
}
