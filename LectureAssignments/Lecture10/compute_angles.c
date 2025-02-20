#include "quad.h"
void compute_angles(quadrilateral_t *quad) {
  quad->inner_angles[0] = compute_angle(quad->node1, quad->node2, quad->node4);
  quad->inner_angles[1] = compute_angle(quad->node2, quad->node4, quad->node1) +
                          compute_angle(quad->node2, quad->node3, quad->node4);
  quad->inner_angles[2] = compute_angle(quad->node3, quad->node4, quad->node2);
  quad->inner_angles[3] = compute_angle(quad->node4, quad->node1, quad->node2) +
                          compute_angle(quad->node4, quad->node2, quad->node3);
}

double compute_angle(point_t p1, point_t p2, point_t p3) {
  // Points enterend in counter clockwise order. P1 is angle to solve
  double a = distance(p3, p1);
  double b = distance(p1, p2);
  double c = distance(p2, p3);
  double radian_value =
      acos((pow(c, 2) - (pow(a, 2) + pow(b, 2))) / (-1 * 2 * a * b));
  return radian_value * (180.0 / M_PI);
}
