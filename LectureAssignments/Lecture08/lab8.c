#include "lab8.h"

int main(int argc, char *argv[]) {
  printf("%d\n", factorial(10));
  printf("%lf\n", myexp(2.12));
  return 0;
}

int factorial(int x) {
  // Function will get factorial of x.
  // X cannot be too big to get factorial
  // X cannot be negative
  if (x == 0) {
    return 1;
  }
  if (x < 0) {
    printf("factorial of negative is undefined");
    return 0;
  }
  return factorial(x - 1) * x;
}

double myexp(double x) {
  // Function computes e^x using taylor expansion
  // e is constant
  // tolerance val is set and max of 10 iterations
  //
  double tolerance = 0.00000000000001;
  double e = 2.718281828459;

  int x_0 = (int)round(x);
  double z = x - x_0;
  double e_to_z = 0;
  int i;
  for (i = 0; i < 10; i++) {
    double value_to_add = pow(z, i) / (double)factorial(i);
    if (fabs(value_to_add) < tolerance) {
      break;
    }
    e_to_z += value_to_add;
  }
  return pow(e, x_0) * e_to_z;
}
