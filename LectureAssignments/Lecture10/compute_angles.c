#include "quad.h"
void compute_angles(quadrilateral_t *quad) {}

double compute_angle(point_t p1, point_t p2, point_t p3) {
  // Points enterend in counter clockwise order. P1 is angle to solve

  double a = distance(p3, p1);
  double b = distance(p1, p2);
  double c = distance(p2, p3);
  double radian_value =
      acos((pow(c, 2) - (pow(a, 2) + pow(b, 2))) / (-1 * 2 * a * b));
  return radian_value * (180.0 / M_PI);
}
