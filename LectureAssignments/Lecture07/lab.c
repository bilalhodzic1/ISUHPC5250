#include <limits.h>
#include <math.h>
#include <stdio.h>

int main() {
  // Logic for factorial
  // Get a number
  printf("Enter a number to be get the factorial of that number:\n");
  int n;
  scanf("%d", &n);
  int factorial = 1;
  int i;
  // Check if factorial will not fit in an int
  if (n > 12) {
    printf("This will be too big");
  } else {
    // Compute facotorial
    for (i = 1; i <= n; i++) {
      factorial *= i;
    }
  }
  // Print result
  printf("End result is %d\n", factorial);
  // Get value for e^x
  printf("Enter a real number to take e to power of: \n");
  float x;
  scanf("%f", &x);
  // Use math to get result and print
  float result = exp(x);
  printf("Result of e^%f : %f\n", x, result);

  // Get value for ln(x)
  printf("Enter a number to take ln(x) of: \n");
  float y;
  scanf("%f", &y);
  // Use math and print result
  float result_y = log(y);
  printf("Result of ln(%f): %f\n", y, result_y);

  // Indicate successful completion of main
  return 0;
}
