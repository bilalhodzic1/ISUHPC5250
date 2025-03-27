#include "simpsons.h"
int main(int argc, char *argv[]) {
  int N = 5;
  double val_a = 1.0;
  double val_b = 2.0;
  double *points = generate_set_of_points(val_a, val_b, N);
  double *values = (double *)malloc(sizeof(double) * (N + 1));
  int i;
  for (i = 0; i < 5 + 1; i++) {
    values[i] = func(points[i]);
  }
  return 0;
}
double func(const double x) { return (1.0 + exp(x)); }
