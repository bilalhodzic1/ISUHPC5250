#include "simpsons.h"
double local_simpson_computation(double val_a, double val_b, int N) {
#ifdef _OPENMP
  const int my_rank = omp_get_thread_num();
  const int thread_count = omp_get_num_threads();
#else
  const int my_rank = 0;
  const int thread_count = 1;
#endif
  double h = (val_b - val_a) / (double)N;
  double T_local = 0.0;
  double local_N = N / thread_count;
  double local_a = val_a + my_rank * local_N * h;
  double local_b = local_a + local_N * h;
  int i;
  for (i = 0; i < local_N; i += 2) {
    printf("I VAL : %d\n", i);
    double x_0 = local_a + (i * h);
    double x_1 = local_a + ((i + 1) * h);
    double x_2 = local_a + ((i + 2) * h);
    printf("%lf, %lf, %lf\n", x_0, x_1, x_2);
    double sum = func(local_a + (i * h)) + 4.0 * func(local_a + ((i + 1) * h)) +
                 func(local_a + ((i + 2) * h));
    T_local += sum;
  }
  T_local *= (h / 3);
  return T_local;
}
