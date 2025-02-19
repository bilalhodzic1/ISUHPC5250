#include "chebyshev.h"
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
  float *x_points = gen_set_of_points(-1, .1, 1, &num_points);
  float y_points[num_points];
  evaluate_polynomial(x_points, coefficients, y_points, degree, num_points);

  FILE *output_file = fopen("output.data", "w");
  // Write values to output
  for (int i = 0; i < num_points; i++) {
    fprintf(output_file, "(%f,%lf)\n", x_points[i], y_points[i]);
  }
  // close file
  fclose(output_file);

  return 0;
}

void evaluate_polynomial(float x_points[], float coeffecients[],
                         float y_points[], int degree, int num_points) {
  int i;
  for (i = 0; i < num_points; i++) {
    y_points[i] = coeffecients[0];
    int k;
    double phi;
    for (k = 1; k <= degree; k++) {
      switch (k) {
      case 1:
        phi = x_points[i];
        break;
      case 2:
        phi = 2 * pow(x_points[i], 2) - 1;
        break;
      case 3:
        phi = 4 * pow(x_points[i], 3) - (3 * x_points[i]);
        break;
      case 4:
        phi = 8 * pow(x_points[i], 4) - 8 * pow(x_points[i], 2) + 1;
        break;
      case 5:
        phi = 16 * pow(x_points[i], 5) - 20 * pow(x_points[i], 3) +
              5 * x_points[i];
        break;
      }
      y_points[i] += phi;
    }
  }
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
