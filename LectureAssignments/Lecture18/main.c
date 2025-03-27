#include "simpsons.h"
#include <stdlib.h>
int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Wrong number of arguements!\n");
    exit(1);
  }
  int N = atoi(argv[2]);
  int thread_count = atoi(argv[1]);
  double val_a = 1;
  double val_b = 2;
  double critical_result =
      critical_simpson_computation(val_a, val_b, N, thread_count);
  double reduction_resilt =
      reduction_simpson_computation(val_a, val_b, N, thread_count);
  printf("Crit : %lf\n Red : %lf", critical_result, reduction_resilt);
  return 0;
}
