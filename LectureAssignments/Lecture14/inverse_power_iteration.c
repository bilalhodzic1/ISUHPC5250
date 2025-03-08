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
  double tolerance = 0.0000000000001;
  while (!m_stop) {
    matrix mu_I = new_matrix(A->rows, A->cols);
    int i;
    for (i = 0; i < mu_I.rows; i++) {
      mget(mu_I, i + 1, i + 1) = mu * 1;
    }
    matrix A_minus_mu_I = matrix_sub(A, &mu_I);
    k = k + 1;
    vector w = solve(&A_minus_mu_I, &v_0);
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
