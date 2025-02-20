#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct point {
  float x;
  float y;
} point_t;

typedef struct quadrilateral {
  point_t node1;
  point_t node2;
  point_t node3;
  point_t node4;
  double area;
  double perimeter;
  double inner_angles[4];
} quadrilateral_t;

void quad_area(quadrilateral_t *quad);
void quad_perimeter(quadrilateral_t *quad);
void compute_angles(quadrilateral_t *quad);
void print_details(quadrilateral_t quad);
