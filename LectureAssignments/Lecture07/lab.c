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
  return 0;
}
