#include "node.h"
int main(int argc, char *argv[]) {
  int num_nodes = get_num_of_nodes();
  node_t *head = NULL;
  generate_list(&head, num_nodes);
  print(0, head);
  print(1, head);
  delete_list(&head);
  char user_input = get_key();
  printf("%c\n", user_input);
  while (user_input != '0') {
    search_list(head, user_input);
    user_input = get_key();
  }

  return 0;
}
