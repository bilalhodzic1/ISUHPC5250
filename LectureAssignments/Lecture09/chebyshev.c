#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int n_max = 5;
  int i;
  printf("Please enter the degree of your polynomial\n");
  int degree;
  scanf("%d", &degree);
  if (degree < 0 || degree > 5) {
    printf("Invalid Degree");
    exit(0);
  }
  float coefficients[degree];
  for (i = 0; i < degree; i++) {
    printf("Enter coefficient %d\n", i + 1);
    scanf("%f", &coefficients[i]);
  }

  for (i = 0; i < degree; i++) {
    printf("%f\n", coefficients[i]);
  }

  return 0;
}
