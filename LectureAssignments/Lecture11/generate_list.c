#include "node.h"

void generate_list(node_t **head, const int num_nodes) {
  srand(time(NULL));
  node_t *temp;
  int i;
  for (i = 0; i < num_nodes; i++) {
    temp = (node_t *)malloc(sizeof(node_t));
    temp->position = i + 1;
    int is_upper = rand() % 2;
    if (is_upper) {
      temp->letter = rand() % 26 + 65;
    } else {
      temp->letter = rand() % 26 + 97;
    }

    if (*head == NULL) {
      *head = temp;
      (*head)->next = NULL;
    } else {
      temp->next = *head;
      *head = temp;
    }
  }
}
