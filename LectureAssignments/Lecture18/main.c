#include "simpsons.h"
int main(int argc, char *argv[]) {
  int N = 6;
  double val_a = 1.0;
  double val_b = 2.0;
  double T = 0.0;
  const double time1 = omp_get_wtime();
#pragma omp parallel num_threads(thread_count)
  {
    double T_local = LocalCompTrap(a, b, N);
#pragma omp critical
    T += T_local;
  }
  const double time2 = omp_get_wtime();
  double result = simpson_computation(val_a, val_b, N);
  printf("%lf\n", result);
  return 0;
}
