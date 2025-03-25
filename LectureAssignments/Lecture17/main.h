#ifndef __MAIN_H__
#define __MAIN_H__
#include "matrix.h"
#ifdef _OPENMP
#include <omp.h>
#endif

void make_output_vector(int num_threads, int vector_size, int degree_k);
#endif
