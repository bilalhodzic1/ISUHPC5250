#include "main.h"

void max_normalize_vector_coarse(int num_threads, int N) {
  vector v = new_vector(N);
  for (int i = 1; i <= N; i++) {
    vget(v, i) = i;
  }

#pragma omp parallel num_threads(num_threads)
  {
    const int local_rank = omp_get_thread_num();

    const int N_per_thread = N / num_threads;
    const int local_i_start = local_rank * N_per_thread + 1;
    const int local_i_end = (local_rank + 1) * N_per_thread;

    double norm = 0.0;
    for (int i = local_i_start; i <= local_i_end; i++) {
#pragma omp critical
      {
        if (vget(v, i) > norm) {
          norm = vget(v, i);
        }
      }
    }
#pragma omp barrier

    for (int i = local_i_start; i <= local_i_end; i++) {
      vget(v, i) = vget(v, i) / norm;
    }
  }
}
