#include "matrix.h"
#include <stdlib.h>
#include <time.h>
/**
 * @brief creates an upper triangle matrix with 1s on diagonals and random
 * numbers between 0 and 1 on the lower half
 *
 * @param mat: a pointer to a matrix object that will be made an upper triangle
 * matrix
 *
 * @return nothing. function is void
 */
void create_upper_triangle(matrix *mat) {
  // Decalre srand for true random
  srand(time(NULL));
  int i, j;
  // fill diag with ones
  for (i = 0; i < mat->rows; i++) {
    mgetp(mat, i + 1, i + 1) = 1;
  }
  // Iterate through in a way where only the lower triangle will be filled
  for (i = 1; i <= mat->rows; i++) {
    for (j = 0; j < i - 1; j++) {
      mgetp(mat, i, j + 1) = (rand() + 1.0) / (RAND_MAX + 2.0);
    }
  }
}
/**
 * @brief generates a matrix to solve eiganvalues for based on the in class spec
 *
 * @return a matrix instance filled with the values that adhere to the
 * specification
 */
matrix generate_matrix_for_solve() {
  // Declare a new 6x6 matrix
  matrix L = new_matrix(6, 6);
  // Compute upper traingle
  create_upper_triangle(&L);
  // Tranposed L times L operation
  matrix L_T = transpose_matrix(&L);
  matrix result = matrix_mult(&L, &L_T);
  return result;
}
