#include "matrix.h"

void fill_random_vector(vector *v) {
  srand(time(NULL));
  int i;
  for (i = 0; i < v->size; i++) {
    vgetp(v, i + 1) = (rand() + 1.0) / (RAND_MAX + 2.0);
  }
}
