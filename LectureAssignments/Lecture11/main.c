#include "node.h"
int main(int argc, char *argv[]) {
  int num_nodes = get_num_of_nodes();
  node_t *head = NULL;
  generate_list(&head, num_nodes);
  print(0, head);
  print(1, head);
  printf("\n");
  char user_input = get_key();
  while (user_input != '0') {
    search_list(head, user_input);
    user_input = get_key();
  }
  delete_list(&head);
  return 0;
}
