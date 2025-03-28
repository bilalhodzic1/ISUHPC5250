#include "simpsons.h"
/**
 * @brief conducts simpsons method for approximating an integral using the
 * openmp reduction method for parallelization
 *
 * @param val_a: a double representing the starting value of the integral
 * @param val_b: a double representing the ending value of the integral
 * @param N: the number of points to conduct the computation on
 * @param num_threads: the number of threads to be used in parallelization
 * @return a double which is the result of the integral
 */
double reduction_simpson_computation(double val_a, double val_b, int N,
                                     int num_threads) {
  // declare initial sum variable
  double T = 0.0;
  // get initial time for computing
  const double time1 = omp_get_wtime();
  // conduct the computation using reduction
#pragma omp parallel num_threads(num_threads) reduction(+ : T)
  T += local_simpson_computation(val_a, val_b, N);
  // get the final time
  const double time2 = omp_get_wtime();
  // Print all relevant results
  printf("\nReduction timings: \n");
  printf("Time 1: %lf, ", time1);
  printf("Time 2: %lf, ", time2);
  printf("N: %d, ", N);
  printf("T: %lf, ", T);
  printf("Number Threads: %d, ", num_threads);
  const double clock_time = time2 - time1;
  printf("Total time %11.5e\n", clock_time);
  // Return the value of the integral
  return T;
}
