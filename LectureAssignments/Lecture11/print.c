#include "node.h"

void print_detail_line(int pos, char value, const node_t *current,
                       const node_t *next) {
  printf("|%3d|%3c|%12p|%12p|", pos, value, current, next);
}

void print(const int forward, const node_t *head) {
  printf("\n");
  printf(" ---------------------------------------------\n");
  printf(" |Pos :| Val :| Address : | Next: |\n");
  printf(" ---------------------------------------------\n");
  switch (forward) {
  case 1:
    print_list(head);
    break;
  case 2:
    print_list_reverse(head);
    break;
  }
}
void print_list(const node_t *head) {
  print_detail_line(head->position, head->letter, head, head->next);
  if (head->next == NULL) {
    return;
  }
  print_list(head->next);
}
void print_list_reverse(const node_t *head) {}
