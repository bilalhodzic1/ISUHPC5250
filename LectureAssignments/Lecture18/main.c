#include "simpsons.h"
int main(int argc, char *argv[]) {
  double *points = generate_set_of_points(1.0, 2.0, 5);
  int i;
  for (i = 0; i < 5 + 1; i++) {
    printf("Points[%d] : %lf\n", i, points[i]);
  }
  return 0;
}
