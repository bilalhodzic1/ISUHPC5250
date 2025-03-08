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
  double test_eval = power_iteration(&A);
  printf("%lf\n", test_eval);
  double inverse_power = inverse_power_iteration(&A, 2.0);
  printf("%lf\n", inverse_power);
  return 0;
}
