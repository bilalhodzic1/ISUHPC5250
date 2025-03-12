#include "matrix.h"
#include "trimatrix.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  matrix A = generate_matrix_for_solve();
  trimatrix T = new_trimatrix(6);
  void Hessenberg(const matrix *A, trimatrix *T);
  Hessenberg(&A, &T);
  printf("\n");
  printf(" Original Matrix :\n");
  print_matrix(&A);
  printf(" Reduction to Tridiagonal Form :\n");
  print_trimatrix(&T);

  // QR Algorithm to find eigenvalues of T
  // which are the same as the eigenvalues of A
  void QRA(trimatrix * T);
  QRA(&T);
  printf(" After QR Algorithm :\n");
  print_trimatrix(&T);
  return 0;
}
