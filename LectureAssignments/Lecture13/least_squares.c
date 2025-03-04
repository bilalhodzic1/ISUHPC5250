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

vector least_squares(const vector *x, const vector *f, const int k) {
  matrix A = new_matrix(x->size, k + 1);
  int i, j;
  for (i = 1; i <= x->size; i++) {
    for (j = 0; j <= k; j++) {
      mget(A, i, j + 1) = pow(vgetp(x, i), j);
    }
  }
  if (x->size == k) {
    return solve(&A, f);
  } else {
    matrix A_T = transpose_matrix(&A);
    matrix to_solve_matrix = matrix_mult(&A_T, &A);
    vector right_result = matrix_vector_mult(&A_T, f);
    return solve(&to_solve_matrix, &right_result);
  }
}
