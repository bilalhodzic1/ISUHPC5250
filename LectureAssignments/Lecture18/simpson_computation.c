#include "simpsons.h"
/**
 * @brief a serial version of the simpson computation for approximating an
 * integral
 *
 * @param val_a: a double representing the start value of the integral
 * @param val_b: a double representing the end value of the integral
 * @param N: number of points to conduct the computation on
 *
 * @return a double representing the evaluation of the integral
 */
double simpson_computation(double val_a, double val_b, int N) {
  // calculate the distance betwen points
  double h = (val_b - val_a) / (double)N;
  double T = 0.0;
  int i;
  // conduct the approximation by summing the points
  for (i = 0; i < N; i += 2) {
    double x_0 = val_a + (i * h);
    double x_1 = val_a + ((i + 1) * h);
    double x_2 = val_a + ((i + 2) * h);
    double sum = func(val_a + (i * h)) + 4.0 * func(val_a + ((i + 1) * h)) +
                 func(val_a + ((i + 2) * h));
    T += sum;
  }
  // return the result
  T *= (h / 3);
  return T;
}

// This is e^x
double func(const double x) { return exp(x); }
