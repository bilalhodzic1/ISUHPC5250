#include "main.h"
#include "matrix.h"
/**
 * @brief normalizes a vector using infinity normalization (max norm) and logs
 * the time it takes to complete using fine grained parallelization
 *
 * @param N: the number of values in the vector
 * @param num_threads: the number of threads to run in parallel
 *
 * @return nothing the function is void
 */
void max_normalize_vector_fine(int num_threads, int N) {
  // Create vector of N size incrementing from 1 to N for testing
  vector v = new_vector(N);
  for (int i = 1; i <= N; i++) {
    vget(v, i) = i;
  }
  // Declare norm variable and get initial time
  double norm = 0.0;
  const double time1 = omp_get_wtime();
// Declare a fine graned parallel block of size num_threads
#pragma omp parallel num_threads(num_threads)
  {
    // Declare a max reduction block allowing all threads to work at same time
    // and compute the global max value
#pragma omp for reduction(max : norm)
    for (int i = 1; i <= N; i++) {
      if (vget(v, i) > norm) {
        norm = vget(v, i);
      }
    }
    // Declare a barrier to wait for thread completion (Not neccarssy as there
    // is an implicit barrier with the reduction)
#pragma omp barrier
    // Declare a fine grained for block allowing all threads to work in sync to
    // normalize the vector
#pragma omp for
    for (int i = 1; i <= N; i++) {
      vget(v, i) = vget(v, i) / norm;
    }
  }
  // Get the end time and the total time
  const double time2 = omp_get_wtime();
  const double clock_time = time2 - time1;
  // Print the results
  printf("Max norm fine : [Num Threads: %d, Norm: %lf, V[0]: %lf, V[N-1]: %lf, "
         "Clock time: "
         "%11.5e]\n",
         num_threads, norm, vget(v, 1), vget(v, N), clock_time);
}
