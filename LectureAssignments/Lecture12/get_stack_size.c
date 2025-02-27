#include "node.h"
/**
 * @brief  Gets the size of the current stack. Size is the number of nodes
 *
 * @param  top A reference to the current top of the stack
 * @return The size of the stack as an int
 */
int get_stack_size(node_t **top) {
  if ((*top) == NULL) {
    return 0;
  } else {
    int count = 1;
    node_t *tracer = *top;
    while (tracer != NULL) {
      tracer = tracer->next;
      count++;
    }
    return count;
  }
}
