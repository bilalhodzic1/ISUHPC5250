#include "main.h"

void two_normalize_vector_fine(int num_threads, int N) {
  vector v = new_vector(N);
  for (int i = 1; i <= N; i++) {
    vget(v, i) = 1;
  }

  double norm = 0.0;

  const double time1 = omp_get_wtime();

#pragma omp parallel num_threads(num_threads)
  {
#pragma omp for reduction(+ : norm)
    for (int i = 1; i <= N; i++) {
      norm += pow(vget(v, i), 2);
    }
#pragma omp barrier
    norm = sqrt(norm);
#pragma omp for
    for (int i = 1; i <= N; i++) {
      vget(v, i) = vget(v, i) / norm;
    }
  }

  const double time2 = omp_get_wtime();
  const double clock_time = time2 - time1;

  printf("Num Threads: %d, Norm: %lf, V[0]: %lf, V[N-1]: %lf, Clock time: "
         "%11.5e\n",
         num_threads, norm, vget(v, 1), vget(v, N), clock_time);
}
