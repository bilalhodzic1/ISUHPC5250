#include "matrix.h"
/**
 * @brief subtracts two matricies. Must be same size matricies
 *
 * @param A: a matrix A
 * @param B: a matrix B to subtract from A
 *
 * @return a matrix instance that contains the values corresponding to A - B
 */
matrix matrix_sub(const matrix *A, const matrix *B) {
  // Assert matricies have the same dimensions
  assert(A->rows == B->rows);
  assert(A->cols == B->cols);
  // Declare new matrix
  matrix result = new_matrix(A->rows, A->cols);
  // Conduct substraction
  int i, j;
  for (i = 0; i < result.rows; i++) {
    for (j = 0; j < result.cols; j++) {
      mget(result, i + 1, j + 1) =
          mgetp(A, i + 1, j + 1) - mgetp(B, i + 1, j + 1);
    }
  }
  // Return result
  return result;
}
