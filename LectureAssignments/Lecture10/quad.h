#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct vector {
  float x;
  float y;
  float z;
} vector_t;

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
vector_t simple_cross_product(vector_t v1, vector_t v2);
vector_t make_xy_vector(point_t p1, point_t p2);
double distance(point_t p1, point_t p2);
