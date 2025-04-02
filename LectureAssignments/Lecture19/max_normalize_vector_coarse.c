#include "main.h"
/**
 * @brief normalizes a vector using infinity normalization (max norm) and logs
 * the time it takes to complete using coarse grained parallelization
 *
 * @param N: the number of values in the vector
 * @param num_threads: the number of threads to run in parallel
 *
 * @return nothing the function is void
 */
void max_normalize_vector_coarse(int num_threads, int N) {
  // create a vector of N size and fill with acsending values for testing
  vector v = new_vector(N);
  for (int i = 1; i <= N; i++) {
    vget(v, i) = i;
  }
  // log initial time and create norm variable
  double norm = 0.0;
  const double time1 = omp_get_wtime();
// start a coarse parallel block of size num_threads
#pragma omp parallel num_threads(num_threads)
  {
    // Get local rank and local start and end
    const int local_rank = omp_get_thread_num();

    const int N_per_thread = N / num_threads;
    const int local_i_start = local_rank * N_per_thread + 1;
    const int local_i_end = (local_rank + 1) * N_per_thread;
    // Find the max in the threads section of the entire vector
    double thread_norm = 0.0;
    for (int i = local_i_start; i <= local_i_end; i++) {
      if (vget(v, i) > thread_norm) {
        thread_norm = vget(v, i);
      }
    }
// Declare a critical zone for computing global max. Must be critical as threads
// cannot access this value at same time or results may become unexpected
#pragma omp critical
    {
      if (thread_norm > norm) {
        norm = thread_norm;
      }
    }
    // Declare a barrier forcing all theads to finish before continueing
#pragma omp barrier
    // Loop through local section of vector and apply normalization
    for (int i = local_i_start; i <= local_i_end; i++) {
      vget(v, i) = vget(v, i) / norm;
    }
  }
  // Get end time and total time
  const double time2 = omp_get_wtime();
  const double clock_time = time2 - time1;
  // Print results
  printf(
      "Max norm coarse: [Num Threads: %d, Norm: %lf, V[0]: %lf, V[N-1]: %lf, "
      "Clock time: "
      "%11.5e]\n",
      num_threads, norm, vget(v, 1), vget(v, N), clock_time);
}
