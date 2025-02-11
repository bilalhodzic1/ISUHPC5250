#include <limits.h>
#include <math.h>
#include <stdio.h>

int main() {
  printf("Enter a number to be get the factorial of that number:\n");
  int n;
  scanf("%d", &n);
  int factorial = 1;
  int i;
  if (n > 12) {
    printf("This will be too big");
  } else {
    for (i = 1; i <= n; i++) {
      factorial *= i;
    }
  }
  printf("End result is %d\n", factorial);

  printf("Enter a real number to take e to power of \n");
  float x;
  scanf("%f", &x);
  float result = exp(x);
  printf("Result of e^%f : %f\n", x, result);
  return 0;
}
