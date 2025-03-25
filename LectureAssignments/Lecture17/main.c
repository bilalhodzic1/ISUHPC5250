#include "main.h"

int main(int argc, char *argv[]) {
  int num_threads = atoi(argv[1]);
  int vector_size = atoi(argv[2]);
  int degree_k = atoi(argv[3]);
  make_output_vector(num_threads, vector_size, degree_k);
  return 0;
}
