#include "main.h"
int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Wrong number of arguements!");
  }
  int N = atoi(argv[1]);
  int num_threads = atoi(argv[2]);
  max_normalize_vector_fine(num_threads, N);
  two_normalize_vector_fine(num_threads, N);
  max_normalize_vector_coarse(num_threads, N);
  two_normalize_vector_coarse(num_threads, N);
  return 0;
}
