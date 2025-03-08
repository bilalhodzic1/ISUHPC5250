#include "evals.h"
/**
 * @brief conduct rayleigh quotient iteration algorithm to find an eiganvalue
 * within a matrix
 *
 * @param A: a matrix to find an eiganvalue of
 * @param v_0: initial vector to use to find the eiganvalue
 *
 * @return a double representing an eiganvalue of matrix A
 */
double rayleigh_quotient_iteration(matrix *A, vector *v_0) {
  // Noramlize inputted vector and compute first rayleigh quotient
  normalize_vector(v_0);
  matrix v_0_t = transpose_vector(v_0);
  matrix v_0_t_times_A = matrix_mult(&v_0_t, A);
  double eval = vget(matrix_vector_mult(&v_0_t_times_A, v_0), 1);
  // Declare needed loop params
  int m_stop = 0;
  int k = 0;
  int max_iters = 100;
  // Declare tolerance value to stop iteration early
  double tolerance = 0.0000000000001;
  while (!m_stop) {
    // compute new matrix muI where mu is the current eiganvalue guess
    matrix mu_I = new_matrix(A->rows, A->cols);
    int i;
    for (i = 0; i < mu_I.rows; i++) {
      mget(mu_I, i + 1, i + 1) = eval * 1;
    }
    // Compute A - muI
    matrix A_minus_mu_I = matrix_sub(A, &mu_I);
    // Increment k
    k = k + 1;
    // Find w vector by solving lienar system and normalize
    vector w = solve(&A_minus_mu_I, v_0);
    normalize_vector(&w);
    // Set v_k = w
    *v_0 = w;
    // Find new eiganvalue guess
    matrix v_k_t = transpose_vector(v_0);
    matrix v_k_t_times_A = matrix_mult(&v_k_t, A);
    double temp_eval = vget(matrix_vector_mult(&v_k_t_times_A, v_0), 1);
    // Check if eiganvalue k and k-1 difference is within tolerance
    if (fabs(temp_eval - eval) < tolerance) {
      m_stop = 1;
    }
    // Check if we reached the max amount of iterations
    if (k == max_iters) {
      m_stop = 1;
    }
    eval = temp_eval;
  }
  // Return eiganvalue
  return eval;
}
