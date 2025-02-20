#include "quad.h"

void quad_area(quadrilateral_t *quad) {
  vector_t v1 = make_xy_vector(quad->node3, quad->node2);
  vector_t v2 = make_xy_vector(quad->node3, quad->node4);
  vector_t v3 = make_xy_vector(quad->node1, quad->node2);
  vector_t v4 = make_xy_vector(quad->node1, quad->node4);
  vector_t v1_cross_v2 = simple_cross_product(v1, v2);
  vector_t v3_cross_v4 = simple_cross_product(v3, v4);
  quad->area = .5 * fabs(v1_cross_v2.z) + .5 * fabs(v3_cross_v4.z);
}
