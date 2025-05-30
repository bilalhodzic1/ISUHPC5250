#include "matrix.h"
#include <stdio.h>
int main(int argc, char *argv[]) {
  // Declare and generate x vecotr and f vecotr off of given points and
  // functions
  int num_points;
  double *x_points = gen_set_of_points(0.05, 0.05, 1, &num_points);
  vector x_points_vector = new_vector(num_points);
  vector f_points_vector = new_vector(num_points);
  int i;
  for (i = 1; i <= num_points; i++) {
    vget(x_points_vector, i) = x_points[i - 1];
    vget(f_points_vector, i) = sin(2 * M_PI * x_points[i - 1]);
  }
  // Compute least squares and poly interpolation using the least squares
  // function
  vector coeffecients_least_squares_5 =
      least_squares(&x_points_vector, &f_points_vector, 5);
  vector coeffecients_poly_interp =
      least_squares(&x_points_vector, &f_points_vector, num_points - 1);
  // Evaulate the given polynomials computed
  vector y_points_least_squares = evaluate_polynomial(
      &x_points_vector, &coeffecients_least_squares_5, 5, num_points);
  vector y_points_poly_interp = evaluate_polynomial(
      &x_points_vector, &coeffecients_poly_interp, num_points - 1, num_points);
  // Dump outputs to files
  FILE *output_file = fopen("output.data", "w");
  for (i = 1; i <= num_points; i++) {
    fprintf(output_file, "(%lf,%lf)\n", vget(x_points_vector, i),
            vget(y_points_least_squares, i));
  }
  fclose(output_file);
  FILE *output_file_2 = fopen("output2.data", "w");
  for (i = 1; i <= num_points; i++) {
    fprintf(output_file, "(%lf,%lf)\n", vget(x_points_vector, i),
            vget(y_points_poly_interp, i));
  }
  fclose(output_file_2);
  // Visualize the functoons
  system("python3 plot_output_data.py");
  return 0;
}
