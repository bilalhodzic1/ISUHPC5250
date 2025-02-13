#include "lab8.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  // Print factorial
  printf("%d\n", factorial(10));
  // Print test exp
  printf("%lf\n", myexp(2.12));

  // Generate range of values from 0 to 1 with .02 interval
  int num_vals;
  float *points_to_test = gen_set_of_points(0, .02, 1, &num_vals);

  // Start output file
  FILE *output_file = fopen("output.data", "w");
  // Write exp values to output
  for (int i = 0; i < num_vals; i++) {
    fprintf(output_file, "(%f,%lf)\n", points_to_test[i],
            myexp((double)points_to_test[i]));
  }
  // close file
  fclose(output_file);
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
float *gen_set_of_points(float start_val, float interval, float end_val,
                         int *arr_size) {
  float numvals = (end_val - start_val) / interval;
  if (numvals == (int)numvals) {
    *arr_size = (int)numvals + 1;
    float *range_of_values = malloc(sizeof(float) * numvals);
    int i;
    for (i = 0; i < numvals + 1; i++) {
      range_of_values[i] = start_val + interval * i;
    }
    return range_of_values;
  } else {
    printf("Bad interval value!");
    return NULL;
  }
}
