#include "matrix.h"

/**
 * @brief transposes a matrix
 *
 *
 * @param mat the matrix you want to transpose
 *
 * @return a matrix instance that is the input matrix transposed
 */
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

/**
 * @brief computes the least squares fit line from a given matrix and vector
 *
 *
 * @param x a vector of the x points needed to conduct the least squares
 * @param f a vecotr containing the evaulted points from a given fucntion on x
 * @param k the degree of polynomial to generate
 *
 * @return a vector instance containing the coeficents of the function generated
 */
vector least_squares(const vector *x, const vector *f, const int k) {
  matrix A = new_matrix(x->size, k + 1);
  int i, j;
  for (i = 1; i <= x->size; i++) {
    for (j = 0; j <= k; j++) {
      mget(A, i, j + 1) = pow(vgetp(x, i), j);
    }
  }

  if (x->size == k + 1) {
    return solve(&A, f);
  } else {
    matrix A_T = transpose_matrix(&A);
    matrix to_solve_matrix = matrix_mult(&A_T, &A);
    vector right_result = matrix_vector_mult(&A_T, f);
    return solve(&to_solve_matrix, &right_result);
  }
}
