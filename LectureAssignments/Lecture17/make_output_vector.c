#include "main.h"
/**
 * @brief conducts some testing to get speed difference between number of
 * threads using openMP
 *
 * @param num_theads: the number of threads to run the loop with
 * @param vector_size: the size of the vector to conduct the computation
 * @param degree_k: the degree at which to exponentialize the vector values
 *
 * @return nothing, function is void
 */
void make_output_vector(int num_threads, int vector_size, int degree_k) {
  // Make a new vector and fill with random values between 0 and 1
  vector v = new_vector(vector_size);
  fill_random_vector(&v);
  // Create a new vector to store the unused output
  vector output = new_vector(vector_size);
  // Get the time before starting
  const double time1 = omp_get_wtime();
  int i, j;
  // Begin a parrallel loop block allowing the loop to be executed on parrallel
  // threads
#pragma omp parallel for num_threads(num_threads)
  for (i = 1; i < vector_size; i++) {
    // Summate the values to degree k and set output to this
    double sum = 0.0;
    double value = vget(v, i);
    for (j = 0; j <= degree_k; j++) {
      sum += pow(value, j);
    }
    vget(output, i) = sum;
  }
  // Get the end time and print the resulting total time with that number of
  // threads
  const double time2 = omp_get_wtime();
  const double clock_time = time2 - time1;
  printf("With %i threads , clock_time = %11.5e (sec)\n", num_threads,
         clock_time);
}
