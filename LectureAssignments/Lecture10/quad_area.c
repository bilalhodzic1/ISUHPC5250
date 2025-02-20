#include "quad.h"

void quad_area(quadrilateral_t *quad) {}

vector_t simple_cross_product(vector_t v1, vector_t v2) {
  vector_t result;
  result.x = v1.y * v2.z - v2.y * v1.z;
  result.y = v2.x * v1.z - v1.x * v2.z;
  result.z = v1.x * v2.y - v2.x - v1.y;
  return result;
}
vector_t make_xy_vector(point_t p1, point_t p2) {
  vector_t result;
  result.x = p2.x - p1.x;
  result.y = p2.y - p1.y;
  result.z = 0;
  return result;
}
