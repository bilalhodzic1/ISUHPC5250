#include "main.h"

void make_output_vector(int num_threads, int vector_size, int degree_k) {
  vector v = new_vector(vector_size);
  fill_random_vector(&v);
  vector output = new_vector(vector_size);
  const double time1 = omp_get_wtime();
#pragma omp parallel for num_threads(num_threads)
  int i, j;
  for (i = 1; i < vector_size; i++) {
    double sum = 0.0;
    double value = vget(v, i);
    for (j = 0; j <= degree_k; j++) {
      sum += pow(value, j);
    }
    vget(output, i) = sum;
  }
  const double time2 = omp_get_wtime();
  const double clock_time = time2 - time1;
  printf(" With %i threads , clock_time = %11.5e (sec)\n", num_threads,
         clock_time);
}
