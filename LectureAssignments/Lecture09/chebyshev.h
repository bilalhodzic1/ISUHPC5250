#include <math.h>
#include <stdio.h>
#include <stdlib.h>
float *gen_set_of_points(float start_val, float interval, float end_val,
                         int *arr_size);

void evaluate_polynomial(float x_points[], float coeffecients[],
                         float y_points[], int degree);
