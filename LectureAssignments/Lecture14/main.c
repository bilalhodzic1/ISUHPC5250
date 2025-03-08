#include "evals.h"
#include "matrix.h"

int main(int argc, char *argv[]) {
  matrix A = new_matrix(3, 3);
  mget(A, 1, 1) = 0;
  mget(A, 1, 2) = 11;
  mget(A, 1, 3) = -5;
  mget(A, 2, 1) = -2;
  mget(A, 2, 2) = 17;
  mget(A, 2, 3) = -7;
  mget(A, 3, 1) = -4;
  mget(A, 3, 2) = 26;
  mget(A, 3, 3) = -10;
  print_matrix(&A);
  double test_eval = power_iteration(&A);
  printf("%lf\n", test_eval);
  double inverse_power = inverse_power_iteration(&A, 4.2);
  printf("%lf\n", inverse_power);
  vector v_0 = new_vector(A.cols);
  int i;
  for (i = 0; i < A.rows; i++) {
    vget(v_0, i + 1) = mget(A, i + 1, i + 1);
  }
  double rayleigh_power = rayleigh_quotient_iteration(&A, &v_0);
  printf("%lf\n", rayleigh_power);
  return 0;
}
