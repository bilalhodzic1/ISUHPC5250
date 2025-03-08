#include "matrix.h"
#include <math.h>
/**
 * @brief gets the magnitude of a vectpr
 *
 * @param v: a vector that you need the magnitude from
 *
 * @return a double value representing the magnitude of the vector
 */
double get_magnitude(vector *v) {
  // Declare initial magnitude to be 0
  double magnitude = 0.0;
  // Sum all values squared of vector
  int i;
  for (i = 0; i < v->size; i++) {
    magnitude += pow(vgetp(v, i + 1), 2);
  }
  // Return square root of sum
  return sqrt(magnitude);
}
/**
 * @brief normalizes a vector
 *
 * @param v: a vector to be normallized
 *
 * @return nothing, the function is void
 */
void normalize_vector(vector *v) {
  // Get the magnitude of the vector
  double magnitude = get_magnitude(v);
  // Divide all values within the vector with the magnitude
  int i;
  for (i = 0; i < v->size; i++) {
    vgetp(v, i + 1) = vgetp(v, i + 1) / magnitude;
  }
}
