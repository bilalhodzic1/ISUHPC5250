#include "evals.h"
#include "matrix.h"

int main(int argc, char *argv[]) {
  // Generate matrix A
  matrix A = generate_matrix_for_solve();
  // Print what we got
  print_matrix(&A);
  // Conduct power_iteration
  double test_eval = power_iteration(&A);
  printf("Power: %lf\n", test_eval);
  // Conduct inverse_power_iteration
  double inverse_power = inverse_power_iteration(&A, 4.2);
  printf("Inverse power: %lf\n", inverse_power);
  // Make a vector the diagnoal of A
  vector v_0 = new_vector(A.cols);
  int i;
  for (i = 0; i < A.rows; i++) {
    vget(v_0, i + 1) = mget(A, i + 1, i + 1);
  }
  // Conduct rayleigh_quotient_iteration
  double rayleigh_power = rayleigh_quotient_iteration(&A, &v_0);
  printf("Rayleigh: %lf\n", rayleigh_power);
  return 0;
}
