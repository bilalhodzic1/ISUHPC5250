#include "chebyshev.h"
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
  float coefficients[degree + 1];
  for (i = 0; i < degree; i++) {
    printf("Enter coefficient %d\n", i);
    scanf("%f", &coefficients[i]);
  }

  for (i = 0; i < degree; i++) {
    printf("%f\n", coefficients[i]);
  }

  int num_points;
  float *points = gen_set_of_points(-1, .1, 1, &num_points);

  return 0;
}

float *gen_set_of_points(float start_val, float interval, float end_val,
                         int *arr_size) {
  // Generate a set of points from start to end at interval
  // interval must be valid to make make array of size int

  // Get num vals
  float numvals = (end_val - start_val) / interval;
  // Check if num_vals is valud
  if (numvals == (int)numvals) {
    // Create array of size numvals
    *arr_size = (int)numvals + 1;
    float *range_of_values = malloc(sizeof(float) * numvals);
    int i;
    // Generate values and populate array
    for (i = 0; i < numvals + 1; i++) {
      range_of_values[i] = start_val + interval * i;
    }
    // Return array pointer
    return range_of_values;
  } else {
    printf("Bad interval value!");
    return NULL;
  }
}
