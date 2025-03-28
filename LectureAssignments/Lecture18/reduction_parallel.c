#include "simpsons.h"
double reduction_simpson_computation(double val_a, double val_b, int N,
                                     int num_threads) {
  double T = 0.0;
  const double time1 = omp_get_wtime();
#pragma omp parallel num_threads(num_threads) reduction(+ : T)
  T += local_simpson_computation(val_a, val_b, N);
  const double time2 = omp_get_wtime();

  printf("\nReduction timings: \n");
  printf("Time 1: %lf ", time1);
  printf("Time 2: %lf ", time2);
  printf("N: %d", N);
  printf("T: %lf", T);
  printf("Number Threads: %d", num_threads);
  const double clock_time = time2 - time1;
  printf("Total time %11.5e", clock_time);
  return T;
}
