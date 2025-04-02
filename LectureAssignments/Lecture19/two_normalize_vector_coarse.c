#include "main.h"
#include "matrix.h"
#include <math.h>
void two_normalize_vector_coarse(int num_threads, int N) {
  vector v = new_vector(N);
  for (int i = 1; i <= N; i++) {
    vget(v, i) = 1;
  }
  double norm = 0.0;

  const double time1 = omp_get_wtime();

#pragma omp parallel num_threads(num_threads)
  {
    const int local_rank = omp_get_thread_num();

    const int N_per_thread = N / num_threads;
    const int local_i_start = local_rank * N_per_thread + 1;
    const int local_i_end = (local_rank + 1) * N_per_thread;

    double thread_norm = 0.0;
    for (int i = local_i_start; i <= local_i_end; i++) {
      thread_norm += pow(vget(v, i), 2);
    }

#pragma omp critical
    norm += thread_norm;

#pragma omp single
    norm = sqrt(norm);

    for (int i = local_i_start; i <= local_i_end; i++) {
      vget(v, i) = vget(v, i) / norm;
    }
  }
  const double time2 = omp_get_wtime();
  const double clock_time = time2 - time1;

  printf("Two Normal Coarse:[Num Threads: %d, Norm: %lf, V[0]: %lf, V[N-1]: "
         "%lf, Clock time: "
         "%11.5e]\n",
         num_threads, norm, vget(v, 1), vget(v, N), clock_time);
}
