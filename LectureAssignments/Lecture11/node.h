#ifndef __NODE_H__
#define __NODE_H__

typedef struct node node_t;
struct node {
  int position;
  char letter;
  node_t *next;
};

int get_num_of_nodes();
void generate_list(node_t **head, const int num);
void print(const int forward, const node_t *head);
void print_list(const node_t *head);
void print_list_reverse(const node_t *head);
char get_key();
void search_list(const node_t *head, const char key);
void delete_list(node_t **head);
#endif // !__NODE_H__
#define __NODE_H__
