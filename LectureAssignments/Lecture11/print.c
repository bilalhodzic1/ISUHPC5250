#include "node.h"

void print_detail_line(int pos, char value, const node_t *current,
                       const node_t *next) {
  printf(" | %3d | %4c | %15p | %15p |\n", pos, value, current, next);
}

void print(const int forward, const node_t *head) {
  printf("\n");
  printf(" --------------------------------------------------\n");
  printf(" |Pos :| Val :| Address :       | Next:           |\n");
  printf(" --------------------------------------------------\n");
  switch (forward) {
  case 1:
    print_list(head);
    break;
  case 0:
    print_list_reverse(head);
    break;
  }
  printf("\n");
}
void print_list(const node_t *head) {
  print_detail_line(head->position, head->letter, head, head->next);
  if (head->next == NULL) {
    return;
  }
  print_list(head->next);
}
void print_list_reverse(const node_t *head) {
  if (head->next == NULL) {
    print_detail_line(head->position, head->letter, head, head->next);
    return;
  }
  print_list_reverse(head->next);
  print_detail_line(head->position, head->letter, head, head->next);
}
