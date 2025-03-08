#include "matrix.h"
void create_upper_triangle(matrix *mat) {
  srand(time(NULL));
  int i, j;
  for (i = 0; i < mat->rows; i++) {
    mgetp(mat, i + 1, i + 1) = 1;
  }
  for (i = 1; i <= mat->rows; i++) {
    for (j = 0; j < i - 1; j++) {
      mgetp(mat, i, j + 1) = (rand() + 1.0) / (RAND_MAX + 2.0);
    }
  }
}

matrix generate_matrix_for_solve() {
  matrix L = new_matrix(6, 6);
  create_upper_triangle(&L);
  matrix L_T = transpose_matrix(&L);
  matrix result = matrix_mult(&L, &L_T);
  return result;
}
