#include "main.h"
#include <stdlib.h>
int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Wrong number of arguements!");
  }
  int N = atoi(argv[1]);
  int num_threads = atoi(argv[2]);

  return 0;
}
