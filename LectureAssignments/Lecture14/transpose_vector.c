#include "matrix.h"
/**
 * @brief get a transposed version of a vector
 *
 * @param v: a vector to get the tranposed version of
 *
 * @return a matrix object of 1 row representing the transposed vector
 */
matrix transpose_vector(const vector *v) {
  // Declare matrix of 1 row and vecotr size columns
  matrix v_t = new_matrix(1, v->size);
  // Transpose the vector by filling the columns in order
  int i;
  for (i = 0; i < v->size; i++) {
    mget(v_t, 1, i + 1) = vgetp(v, i + 1);
  }
  // Return the tranposed vector
  return v_t;
}
