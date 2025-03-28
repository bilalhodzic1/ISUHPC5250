#include "simpsons.h"
/**
 * @brief Conducts a localization simposons approximation based on the rank of
 * the current thread.
 *
 * @param val_a: the start of the overall range of the integral as a double
 * @param val_b: the end of the overall range of the integral as a double
 * @param N: the total number of points to conduct the approximation on
 *
 * @return a double representing the localized evaluation of the simpson method
 */
double local_simpson_computation(double val_a, double val_b, int N) {
  // Check if openmp exists if yes get the total num of threads and the current
  // thread num
#ifdef _OPENMP
  const int my_rank = omp_get_thread_num();
  const int thread_count = omp_get_num_threads();
#else
  const int my_rank = 0;
  const int thread_count = 1;
#endif
  // compute the interval range and use the thread rank to find the section of
  // points to work on
  double h = (val_b - val_a) / (double)N;
  double T_local = 0.0;
  int local_N = N / thread_count;
  double local_a = val_a + my_rank * local_N * h;
  double local_b = local_a + local_N * h;
  // conduct the simpson sum on that range of points
  int i;
  for (i = 0; i < local_N; i += 2) {
    double sum = func(local_a + (i * h)) + 4.0 * func(local_a + ((i + 1) * h)) +
                 func(local_a + ((i + 2) * h));
    T_local += sum;
  }
  // return the final local value
  T_local *= (h / 3);
  return T_local;
}
