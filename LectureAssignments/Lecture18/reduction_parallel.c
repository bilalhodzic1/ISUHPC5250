#include "simpsons.h"
double reduction_simpson_computation(double val_a, double val_b, int N,
                                     int num_threads) {
  double T = 0.0;
  const double time1 = omp_get_wtime();
#pragma omp parallel num_threads(num_threads) reduction(+ : T)
  T += local_simpson_computation(val_a, val_b, N);
  const double time2 = omp_get_wtime();
  return T;
}
