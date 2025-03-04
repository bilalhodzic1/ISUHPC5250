#include "matrix.h"

double *gen_set_of_points(float start_val, float interval, float end_val,
                          int *arr_size) {
  // Generate a set of points from start to end at interval
  // interval must be valid to make make array of size int

  // Get num vals
  float numvals = (end_val - start_val) / interval;
  // Check if num_vals is valud
  if (numvals == (int)numvals) {
    // Create array of size numvals
    *arr_size = (int)numvals + 1;
    double *range_of_values = malloc(sizeof(double) * numvals + 1);
    int i;
    // Generate values and populate array
    for (i = 0; i < numvals + 1; i++) {
      range_of_values[i] = (double)(start_val + interval * i);
    }
    // Return array pointer
    return range_of_values;
  } else {
    printf("Bad interval value!");
    return NULL;
  }
}
