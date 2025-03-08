#include "evals.h"
#include "matrix.h"
double inverse_power_iteration(matrix *A, double mu) {
  vector v_0 = new_vector(A->cols);
  fill_random_vector(&v_0);
  normalize_vector(&v_0);
  matrix v_0_t = transpose_vector(&v_0);
  matrix v_0_t_times_A = matrix_mult(&v_0_t, A);
  double eval = vget(matrix_vector_mult(&v_0_t_times_A, &v_0), 1);
  int m_stop = 0;
  int k = 0;
  int max_iters = 100;
  matrix I = new_matrix(A->rows, A->cols);
  int i;
  for (i = 0; i < I.rows; i++) {
    mget(I, i + 1, i + 1) = 1;
  }
  print_matrix(&I);
  double tolerance = 0.0000000000001;
  while (!m_stop) {
    k = k + 1;
    vector w = matrix_vector_mult(A, &v_0);
    normalize_vector(&w);
    v_0 = w;
    matrix v_k_t = transpose_vector(&v_0);
    matrix v_k_t_times_A = matrix_mult(&v_k_t, A);
    double temp_eval = vget(matrix_vector_mult(&v_k_t_times_A, &v_0), 1);
    if (fabs(temp_eval - eval) < tolerance) {
      m_stop = 1;
    }
    if (k == max_iters) {
      m_stop = 1;
    }
    eval = temp_eval;
  }
  return eval;
}
