#ifndef _MAIN_
#include "matrix.h"
#ifdef _OPENMP
#include <omp.h>
#endif

void two_normalize_vector_coarse(vector v, int num_threads, int N);
void max_normalize_vector_coarse(vector v, int num_threads, int N);
void two_normalize_vector_fine(vector v, int num_threads, int N);
void max_normalize_vector_fine(vector v, int num_threads, int N);
#endif
