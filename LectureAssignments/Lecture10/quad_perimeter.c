#include "quad.h"
void quad_perimeter(quadrilateral_t *quad) {
  quad->perimeter = 0;
  quad->perimeter += distance(quad->node1, quad->node2);
  quad->perimeter += distance(quad->node2, quad->node3);
  quad->perimeter += distance(quad->node3, quad->node4);
  quad->perimeter += distance(quad->node4, quad->node1);
}
