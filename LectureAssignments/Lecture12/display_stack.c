#include "node.h"
#include <stdio.h>

void print_node(node_t *stack_node) {
  printf("|%15p|%15p|%10d|%10lf|%*s|\n", stack_node, stack_node->next,
         stack_node->po.po_number, stack_node->po.po_amount,
         (int)sizeof(stack_node->po.po_description),
         stack_node->po.po_description);
  printf("---------------------------------------------------------------------"
         "----\n");
  if (stack_node->next == NULL) {
    return;
  }
  print_node(stack_node->next);
}

void display_stack(node_t **top) {
  printf("\n");
  printf("|Purchase order stack|\n");
  if (*top != NULL) {
    printf("|   Address     |    Next       |  PO Num  |PO Amount |%*s|\n",
           (int)sizeof((*top)->po.po_description), "PO Description|\n");
    print_node(*top);
  }
}
