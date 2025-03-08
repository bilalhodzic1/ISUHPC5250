#ifndef __EVALS_H__
#define __EVALS_H__
#include "matrix.h"

double power_iteration(matrix *A);
double inverse_power_iteration(matrix *A, double mu);
double rayleigh_quotient_iteration(matrix *A, vector *v_0);
matrix generate_matrix_for_solve();

#endif
