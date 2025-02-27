#ifndef __NODE_H__
#define __NODE_H__

typedef struct node node_t;
struct node {
  node_t *next;
};

typedef struct purchase_order {
  int po_number;
  double po_amount;
  char *po_description;
} purchase_order_t;

void execute_option(int option);
int query_option();
void delete_stack(node_t **top);
void display_options();
void push(node_t **top, purchase_order_t new_po);
purchase_order_t pop(node **top);
purchase_order_t peek(node **top);
void display_stack(node **top);
int get_stack_size(node **top);

#endif
