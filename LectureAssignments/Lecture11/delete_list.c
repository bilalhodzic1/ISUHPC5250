#include "node.h"

void delete_list(node_t **head) {
  while (*head != NULL) {
    node_t *temp = (*head)->next;
    free(*head);
    *head = temp;
  }
}
