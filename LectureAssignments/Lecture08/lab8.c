#include "lab8.h"

int main(int argc, char *argv[]) {
  printf("%d\n", factorial(10));
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
