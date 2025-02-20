#include "quad.h"
void quad_perimeter(quadrilateral_t *quad) {
  quad->perimeter = 0;
  quad->perimeter += sqrt(pow(quad->node2.x - quad->node1.x, 2) +
                          pow(quad->node2.y - quad->node1.y, 2));
  quad->perimeter += sqrt(pow(quad->node3.x - quad->node2.x, 2) +
                          pow(quad->node3.y - quad->node2.y, 2));
  quad->perimeter += sqrt(pow(quad->node4.x - quad->node3.x, 2) +
                          pow(quad->node4.y - quad->node3.y, 2));
  quad->perimeter += sqrt(pow(quad->node1.x - quad->node4.x, 2) +
                          pow(quad->node1.y - quad->node4.y, 2));
}
