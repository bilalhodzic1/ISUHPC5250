#include "simpsons.h"
int main(int argc, char *argv[]) {
  int N = 360;
  double val_a = 1.0;
  double val_b = 100;
  double result = simpson_computation(val_a, val_b, N);
  printf("%lf\n", result);
  return 0;
}
