#include "matrix.h"
/**
 * @brief fills a vector with random values between 0 and 1
 *
 * @param v: a pointer to a vector
 *
 * @return nothing, function is void
 */
void fill_random_vector(vector *v) {
  // Decalre Srand for true random
  srand(time(NULL));
  // Loop through filling with random values between 0 and 1
  int i;
  for (i = 0; i < v->size; i++) {
    vgetp(v, i + 1) = (rand() + 1.0) / (RAND_MAX + 2.0);
  }
}
