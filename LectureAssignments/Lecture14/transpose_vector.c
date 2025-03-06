#include "matrix.h"

matrix transpose_vector(const vector *v) {
  matrix v_t = new_matrix(1, v->size);
  int i;
  for (i = 0; i < v->size; i++) {
    mget(v_t, 1, i + 1) = vgetp(v, i + 1);
  }
  return v_t;
}
