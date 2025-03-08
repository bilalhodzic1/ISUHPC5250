#include "evals.h"
#include "matrix.h"
/**
 * @brief conducts inverse shifted power iteration algorithm to find the closest
 * eiganvalue to paramter mu
 *
 * @param A: a matrix to find the eiganvalue for
 * @param mu: a value to shift the matrix by
 *
 * @return a double value corresponding to the eiganvalue closest to mu
 */
double inverse_power_iteration(matrix *A, double mu) {
  // Declare vector v_0 and noramlize it
  vector v_0 = new_vector(A->cols);
  fill_random_vector(&v_0);
  normalize_vector(&v_0);
  // Find first rayleigh quotient
  matrix v_0_t = transpose_vector(&v_0);
  matrix v_0_t_times_A = matrix_mult(&v_0_t, A);
  double eval = vget(matrix_vector_mult(&v_0_t_times_A, &v_0), 1);
  // Declare needed loop params
  int m_stop = 0;
  int k = 0;
  int max_iters = 100;
  // Decalre a tolerance value to stop iteration at a certain percison
  double tolerance = 0.0000000000001;
  while (!m_stop) {
    // Decalue a new matrix mu * I
    matrix mu_I = new_matrix(A->rows, A->cols);
    int i;
    for (i = 0; i < mu_I.rows; i++) {
      mget(mu_I, i + 1, i + 1) = mu * 1;
    }
    // Take A - muI
    matrix A_minus_mu_I = matrix_sub(A, &mu_I);
    // Incrmeent k
    k = k + 1;
    // Solve for vector w which will give us v_k
    vector w = solve(&A_minus_mu_I, &v_0);
    // Normalize w and set v_k
    normalize_vector(&w);
    v_0 = w;
    // find rayleigh quotient using new vector w
    matrix v_k_t = transpose_vector(&v_0);
    matrix v_k_t_times_A = matrix_mult(&v_k_t, A);
    double temp_eval = vget(matrix_vector_mult(&v_k_t_times_A, &v_0), 1);
    // Check if difference between eiganvalue k and eiganvalue k-1 are within
    // tolerance
    if (fabs(temp_eval - eval) < tolerance) {
      m_stop = 1;
    }
    // Check if max number of iterations has be reached
    if (k == max_iters) {
      m_stop = 1;
    }
    eval = temp_eval;
  }
  // Return the eiganvalue
  return eval;
}
