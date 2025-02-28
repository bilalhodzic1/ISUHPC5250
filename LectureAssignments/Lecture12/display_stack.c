#include "node.h"
#include <stdio.h>
/**
 * @brief Prints the details associated with one done. then recursively prints
 * the next
 *
 * @param  stack_node the node of the stack you want to print
 * @return nothing, function is void
 */
void print_node(node_t *stack_node) {
  printf("|%15p|%15p|%10d|%10lf|%s", stack_node, stack_node->next,
         stack_node->po.po_number, stack_node->po.po_amount,
         stack_node->po.po_description);
  printf("---------------------------------------------------------------------"
         "----\n");
  if (stack_node->next == NULL) {
    return;
  }
  print_node(stack_node->next);
}
/**
 * @brief Function deisplays the stack with all the headers and annotations
 *
 * @param  top a reference to the top node of the stack
 * @return nothing, function is void
 */
void display_stack(node_t **top) {
  printf("\n");
  printf("|Purchase order stack|\n");
  if (*top != NULL) {
    printf("|   Address     |    Next       |  PO Num  |PO Amount  |%s|\n",
           "PO Description|\n");
    print_node(*top);
  }
}
