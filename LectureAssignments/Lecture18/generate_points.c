#include "simpsons.h"
double *generate_set_of_points(double val_a, double val_b, int N) {
  double *output = (double *)malloc(sizeof(double) * (N + 1));
  double h_val = (val_b - val_a) / (double)N;
  output[0] = val_a;
  int i;
  for (i = 1; i < N; i++) {
    output[i] = val_a + (h_val * i);
  }
  output[N] = val_b;
  return output;
}
