#include "matrix.h"

int main(int argc, char *argv[]) {
  vector test = new_vector(8);
  fill_random_vector(&test);
  print_vector(&test);
  return 0;
}
