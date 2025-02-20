#include "quad.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  quadrilateral_t quad;
  printf("Enter nodes 1 to 4 in order using format (x,y) \n");
  scanf("(%f,%f)\n", &quad.node1.x, &quad.node1.y);
  scanf("(%f,%f)\n", &quad.node2.x, &quad.node2.y);
  scanf("(%f,%f)\n", &quad.node3.x, &quad.node3.y);
  scanf("(%f,%f)", &quad.node4.x, &quad.node4.y);

  quad_perimeter(&quad);
  quad_area(&quad);
  compute_angles(&quad);
  print_details(quad);

  return 0;
}

void print_details(quadrilateral_t quad) {
  printf("Node 1: (%f, %f)\n", quad.node1.x, quad.node1.y);
  printf("Node 2: (%f, %f)\n", quad.node2.x, quad.node2.y);
  printf("Node 3: (%f, %f)\n", quad.node3.x, quad.node3.y);
  printf("Node 4: (%f, %f)\n", quad.node4.x, quad.node4.y);
  printf("Perimeter : %lf\n", quad.perimeter);
  printf("Area : %lf\n", quad.area);
  printf("Angle 1: %lf\n", quad.inner_angles[0]);
  printf("Angle 2: %lf\n", quad.inner_angles[1]);
  printf("Angle 3: %lf\n", quad.inner_angles[2]);
  printf("Angle 4: %lf\n", quad.inner_angles[3]);
}
