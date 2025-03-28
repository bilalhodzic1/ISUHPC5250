#include "simpsons.h"
/**
 * @brief solves an integral of a predefiend function over a pre defined area
 * using simpsons rule. Does so using OPENMP critical zoen for parallelization
 *
 *
 * @param val_a: the start value of the integral range
 * @param val_b: a double representing the end value of the range
 * @param N: the number of points to conduct the approximation on
 * @param num_threads: the number of threads to run in parallel
 *
 * @return a double representing the evaluation of the integral
 */
double critical_simpson_computation(double val_a, double val_b, int N,
                                    int num_threads) {
  // Decalre intial sum variable
  double T = 0.0;
  // get the start time of the comoutation
  const double time1 = omp_get_wtime();
  // Conduct parallelization using the critical region tag
#pragma omp parallel num_threads(num_threads)
  {
    double T_local = local_simpson_computation(val_a, val_b, N);
#pragma omp critical
    T += T_local;
  }
  // get the end time of the computation
  const double time2 = omp_get_wtime();
  // print the relevant results
  printf("Critical zone timings: \n");
  printf("Time 1: %lf, ", time1);
  printf("Time 2: %lf, ", time2);
  printf("N: %d, ", N);
  printf("T: %lf, ", T);
  printf("Number Threads: %d, ", num_threads);
  const double clock_time = time2 - time1;
  printf("Total time %11.5e ", clock_time);
  return T;
}
