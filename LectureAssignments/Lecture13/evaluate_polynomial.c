#include "matrix.h"
/**
 * @brief Evaluates a given polynomial for a list of x coord
 *
 * @param  x_poits a list of x_points as a vector
 * @param coeffecients a list of coeffecients as a vector
 * @param degree the degree of the polynomial
 * @param num_points the number of points in the set of x_points
 *
 * @return A vector instance containing the y values evaluated
 */

vector evaluate_polynomial(vector *x_points, vector *coeffecients, int degree,
                           int num_points) {
  vector y_points = new_vector(num_points);
  int i, j;
  for (i = 1; i <= num_points; i++) {
    for (j = 0; j <= degree; j++) {
      vget(y_points, i) =
          pow(vgetp(x_points, i), j) * vgetp(coeffecients, j + 1);
    }
  }
  return y_points;
}
