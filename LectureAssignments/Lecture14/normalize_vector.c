#include "matrix.h"
#include <math.h>

double get_magnitude(vector *v) {
  double magnitude = 0.0;
  int i;
  for (i = 0; i < v->size; i++) {
    magnitude += pow(vgetp(v, i + 1), 2);
  }
  return sqrt(magnitude);
}

void normalize_vector(vector *v) {
  double magnitude = get_magnitude(v);
  int i;
  for (i = 0; i < v->size; i++) {
    vgetp(v, i + 1) = vgetp(v, i + 1) / magnitude;
  }
}
