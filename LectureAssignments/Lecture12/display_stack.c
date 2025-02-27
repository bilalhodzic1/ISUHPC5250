#include "node.h"
#include <stdio.h>

void print_node(node_t *stack_node) {
  printf("|%p|%p|%d|%lf|%s|\n", stack_node, stack_node->next,
         stack_node->po.po_number, stack_node->po.po_amount,
         stack_node->po.po_description);
  printf("---------------------------------------------------------------------"
         "----\n");
}

void display_stack(node_t **top) {
  printf("\n");
  printf("|Purchase order stack|\n");
  printf("|Address|Next|PO Num|PO Amount|PO Description|\n");
  node_t *tracer = *top;
  while (tracer != NULL) {
    print_node(tracer);
    tracer = tracer->next;
  }
}
