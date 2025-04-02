#include "main.h"
#include "matrix.h"
#include <math.h>
/**
 * @brief normalizes a vector using two norm (L2) and logs
 * the time it takes to complete using coarse grained parallelization
 *
 * @param N: the number of values in the vector
 * @param num_threads: the number of threads to run in parallel
 *
 * @return nothing the function is void
 */
void two_normalize_vector_coarse(int num_threads, int N) {
  // Initialzie vector of size N to all 1 for testing
  vector v = new_vector(N);
  for (int i = 1; i <= N; i++) {
    vget(v, i) = 1;
  }
  // Initialize norm variable and set time
  double norm = 0.0;

  const double time1 = omp_get_wtime();
// Start a coarse grained parallel block of size num_threads
#pragma omp parallel num_threads(num_threads)
  {
    // Compute local rank and N and I values
    const int local_rank = omp_get_thread_num();

    const int N_per_thread = N / num_threads;
    const int local_i_start = local_rank * N_per_thread + 1;
    const int local_i_end = (local_rank + 1) * N_per_thread;
    // Declare thread norm and compute sum on thread interval
    double thread_norm = 0.0;
    for (int i = local_i_start; i <= local_i_end; i++) {
      thread_norm += pow(vget(v, i), 2);
    }
// Declare a criritcal zone for globally summing local norms
#pragma omp critical
    norm += thread_norm;
// Declare a single block to ensure square root is done only one time
#pragma omp single
    norm = sqrt(norm);
    // Noramlize vector for each thread
    for (int i = local_i_start; i <= local_i_end; i++) {
      vget(v, i) = vget(v, i) / norm;
    }
  }
  // Get final time and total time to run
  const double time2 = omp_get_wtime();
  const double clock_time = time2 - time1;
  // print results
  printf("Two Normal Coarse:[Num Threads: %d, Norm: %lf, V[0]: %lf, V[N-1]: "
         "%lf, Clock time: "
         "%11.5e]\n",
         num_threads, norm, vget(v, 1), vget(v, N), clock_time);
}
