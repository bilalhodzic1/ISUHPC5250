#include "evals.h"
#include "matrix.h"
/**
 * @brief conduct the power iteration algorithm to find the largest eiganvalue
 * of a matrix
 *
 * @param A: a matrix to solve for the largest eiganvalue
 *
 * @return a double value representing the largest eiganvalue of the matrix
 */
double power_iteration(matrix *A) {
  // Decalre random vector v_0 and noramlize it
  vector v_0 = new_vector(A->cols);
  fill_random_vector(&v_0);
  normalize_vector(&v_0);
  // Find initial rayleigh quotient
  matrix v_0_t = transpose_vector(&v_0);
  matrix v_0_t_times_A = matrix_mult(&v_0_t, A);
  double eval = vget(matrix_vector_mult(&v_0_t_times_A, &v_0), 1);
  // Declare needed loop parameters
  int m_stop = 0;
  int k = 0;
  int max_iters = 100;
  // Declare tolerance value to stop iteration early
  double tolerance = 0.0000000000001;
  while (!m_stop) {
    // Increment k
    k = k + 1;
    // Find new vector with A * v_k
    vector w = matrix_vector_mult(A, &v_0);
    // Normalize this new vecotr and set to v_k
    normalize_vector(&w);
    v_0 = w;
    // Find new rayleigh quotient
    matrix v_k_t = transpose_vector(&v_0);
    matrix v_k_t_times_A = matrix_mult(&v_k_t, A);
    double temp_eval = vget(matrix_vector_mult(&v_k_t_times_A, &v_0), 1);
    // Check if difference between eiganvalues k and k-1 is within tolerance
    if (fabs(temp_eval - eval) < tolerance) {
      m_stop = 1;
    }
    if (k == max_iters) {
      m_stop = 1;
    }
    eval = temp_eval;
  }
  // Return eiganvalue
  return eval;
}
