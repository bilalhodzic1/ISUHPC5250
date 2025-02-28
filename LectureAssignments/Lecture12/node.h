#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct purchase_order {
  int po_number;
  double po_amount;
  char po_description[45];
} purchase_order_t;

typedef struct node node_t;
struct node {
  purchase_order_t po;
  node_t *next;
};

void execute_option(int option, node_t **top);
purchase_order_t create_new_po();
int query_option();
void delete_stack(node_t **top);
void display_options();
void push(node_t **top, purchase_order_t new_po);
purchase_order_t pop(node_t **top);
purchase_order_t peek(node_t **top);
void display_stack(node_t **top);
int get_stack_size(node_t **top);

#endif
