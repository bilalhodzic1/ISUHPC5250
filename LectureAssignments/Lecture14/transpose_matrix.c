#include "matrix.h"
/**
 * @brief get the tranposed version of an inputted matrix
 *
 * @param mat: matrix to transpose
 *
 * @return a matrix instance that is the transposed version of matrix mat
 */
matrix transpose_matrix(matrix *mat) {
  // Decalre new matrix of equal size
  matrix mat_t = new_matrix(mat->cols, mat->rows);
  // loop through in opposite order to get the transposed version
  int i, j;
  for (i = 1; i <= mat_t.rows; i++) {
    for (j = 1; j <= mat_t.cols; j++) {
      mget(mat_t, i, j) = mgetp(mat, j, i);
    }
  }
  // Return the matrix
  return mat_t;
}
