#include "matrix.h"
int main(int argc, char *argv[]) {
  int num_points;
  double *x_points = gen_set_of_points(0.05, 0.05, 1, &num_points);
  vector x_points_vector = new_vector(num_points);
  vector f_points_vector = new_vector(num_points);
  int i;
  for (i = 1; i <= num_points; i++) {
    vget(x_points_vector, i) = x_points[i - 1];
    vget(f_points_vector, i) = sin(2 * M_PI * x_points[i - 1]);
  }

  vector coeffecients_least_squares_5 =
      least_squares(&x_points_vector, &f_points_vector, 5);
  print_vector(&coeffecients_least_squares_5);
  vector coeffecients_poly_interp =
      least_squares(&x_points_vector, &f_points_vector, num_points - 1);
  print_vector(&coeffecients_poly_interp);
  return 0;
}
