#ifndef _SIMPSONS_H
#define _SIMPSONS_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
double func(const double x);
double simpson_computation(double val_a, double val_b, int N);
double local_simpson_computation(double val_a, double val_b, int N);
#endif
