#include "main.h"
/**
 * @brief normalizes a vector using two norm (L2) and logs
 * the time it takes to complete using fine grained parallelization
 *
 * @param N: the number of values in the vector
 * @param num_threads: the number of threads to run in parallel
 *
 * @return nothing the function is void
 */
void two_normalize_vector_fine(int num_threads, int N) {
  // Intialize a new vector of size N to all 1s
  vector v = new_vector(N);
  for (int i = 1; i <= N; i++) {
    vget(v, i) = 1;
  }
  // initial norm variable and get start time
  double norm = 0.0;

  const double time1 = omp_get_wtime();
// Start a parallel thread block for fine grained computing
#pragma omp parallel num_threads(num_threads)
  {
    // Start a sumation reduction fine grained thread loop
#pragma omp for reduction(+ : norm)
    for (int i = 1; i <= N; i++) {
      norm += pow(vget(v, i), 2);
    }
    // Wait for threads to complete (not needed as the barrier is implicit)
#pragma omp barrier
    norm = sqrt(norm);
    // Normalize the vector with a fine grained parallel block
#pragma omp for
    for (int i = 1; i <= N; i++) {
      vget(v, i) = vget(v, i) / norm;
    }
  }
  // Get final time and total time
  const double time2 = omp_get_wtime();
  const double clock_time = time2 - time1;
  // Print results
  printf("Two Normal Fine:[Num Threads: %d, Norm: %lf, V[0]: %lf, V[N-1]: "
         "%lf, Clock time: "
         "%11.5e]\n",
         num_threads, norm, vget(v, 1), vget(v, N), clock_time);
}
