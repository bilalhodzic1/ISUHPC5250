#include "node.h"
int main(int argc, char *argv[]) {
  int num_nodes = get_num_of_nodes();
  node_t *head = NULL;
  generate_list(&head, num_nodes);
  delete_list(&head);
  return 0;
}
