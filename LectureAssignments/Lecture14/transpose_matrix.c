#include "matrix.h"

matrix transpose_matrix(matrix *mat) {
  matrix mat_t = new_matrix(mat->cols, mat->rows);
  int i, j;
  for (i = 1; i <= mat_t.rows; i++) {
    for (j = 1; j <= mat_t.cols; j++) {
      mget(mat_t, i, j) = mgetp(mat, j, i);
    }
  }
  return mat_t;
}
