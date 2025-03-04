#include "matrix.h"

vector evaluate_polynomial(vector *x_points, vector *coeffecients, int degree,
                           int num_points) {
  vector y_points = new_vector(num_points);
  int i, j;
  for (i = 1; i <= num_points; i++) {
    for (j = 0; j <= degree; j++) {
      vget(y_points, i) =
          vgetp(x_points, i) * pow(vgetp(coeffecients, j + 1), 0);
    }
  }
  return y_points;
}
