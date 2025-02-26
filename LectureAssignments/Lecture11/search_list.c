#include "node.h"

void search_list(const node_t *head, const char key) {
  if (head->letter == key) {
    printf("Found letter at position: %d \n", head->position);
  }
  if (head->next == NULL) {
    printf("\n");
    return;
  }
  search_list(head->next, key);
}
