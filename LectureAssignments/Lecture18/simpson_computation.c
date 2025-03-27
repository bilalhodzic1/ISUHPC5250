#include "simpsons.h"

double simpson_computation(double val_a, double val_b, int N) {
  double h = (val_b - val_a) / (double)N;
  double T = 0.0;
  int i;
  for (i = 0; i < N; i += 2) {
    double x_0 = val_a + (i * h);
    double x_1 = val_a + ((i + 1) * h);
    double x_2 = val_a + ((i + 2) * h);
    double sum = func(val_a + (i * h)) + 4.0 * func(val_a + ((i + 1) * h)) +
                 func(val_a + ((i + 2) * h));
    T += sum;
  }
  T *= (h / 3);
  return T;
}

double func(const double x) { return exp(x); }
