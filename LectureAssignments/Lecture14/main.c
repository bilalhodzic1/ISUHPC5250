#include "evals.h"
#include "matrix.h"

int main(int argc, char *argv[]) {
  vector v_0 = new_vector(3);
  vget(v_0, 1) = 1;
  vget(v_0, 2) = 2;
  vget(v_0, 3) = 3;
  matrix A = new_matrix(3, 3);
  mget(A, 1, 1) = 2;
  mget(A, 1, 2) = 4;
  mget(A, 1, 3) = 9;
  mget(A, 2, 1) = 7;
  mget(A, 2, 2) = 4;
  mget(A, 2, 3) = 6;
  mget(A, 3, 1) = 2;
  mget(A, 3, 2) = 2;
  mget(A, 3, 3) = 6;
  print_matrix(&A);
  // normalize_vector(&v_0);
  matrix v_0_t = transpose_vector(&v_0);
  matrix v_0_t_times_A = matrix_mult(&v_0_t, &A);
  print_matrix(&v_0_t_times_A);
  double eval = vget(matrix_vector_mult(&v_0_t_times_A, &v_0), 1);
  printf("%lf\n", eval);
  double test_eval = power_iteration(&A);
  printf("%lf\n", test_eval);
  double inverse_power = inverse_power_iteration(&A, 2.0);
  return 0;
}
