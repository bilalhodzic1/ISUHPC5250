#include "simpsons.h"
#include <stdlib.h>
int main(int argc, char *argv[]) {
  // check for correct num of arguements
  if (argc != 3) {
    printf("Wrong number of arguements!\n");
    exit(1);
  }
  // convert arguements to ints
  int N = atoi(argv[2]);
  int thread_count = atoi(argv[1]);
  // set range of integral
  double val_a = 0;
  double val_b = 1;
  // try both methods of parallelization
  double critical_result =
      critical_simpson_computation(val_a, val_b, N, thread_count);
  double reduction_resilt =
      reduction_simpson_computation(val_a, val_b, N, thread_count);
  return 0;
}
