#include "matrix.h"
int main(int argc, char *argv[]) {
  int num_points;
  double *x_points = gen_set_of_points(0, 0.05, 1, &num_points);
  printf("%d\n", num_points);
  vector x_points_vector = new_vector(4);
  vector f_points_vector = new_vector(4);

  vget(x_points_vector, 1) = 0;
  vget(x_points_vector, 2) = 1;
  vget(x_points_vector, 3) = 2;
  vget(x_points_vector, 4) = 3;

  vget(f_points_vector, 1) = 3;
  vget(f_points_vector, 2) = 0;
  vget(f_points_vector, 3) = 1;
  vget(f_points_vector, 4) = 3;

  /*
    int i;
    for (i = 1; i <= num_points; i++) {
      vget(x_points_vector, i) = x_points[i - 1];
      vget(f_points_vector, i) = sin(2 * M_PI * x_points[i - 1]);
    }*/

  vector coeffecients_least_squares_5 =
      least_squares(&x_points_vector, &f_points_vector, 3);

  return 0;
}
