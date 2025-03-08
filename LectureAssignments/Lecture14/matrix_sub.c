#include "matrix.h"

matrix matrix_sub(const matrix *A, const matrix *B) {
  assert(A->rows == B->rows);
  assert(A->cols == B->cols);
  matrix result = new_matrix(A->rows, A->cols);
  int i, j;
  for (i = 0; i < result.rows; i++) {
    for (j = 0; j < result.cols; j++) {
      mget(result, i + 1, j + 1) =
          mgetp(A, i + 1, j + 1) - mgetp(B, i + 1, j + 1);
    }
  }
  return result;
}
