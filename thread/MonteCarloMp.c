#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define N 10000000
#define LENGTH 1

int main(void) {
  int count_in = 0, count_all = 0;

  srand(time(NULL));

  double x, y;

  #pragma omp parallel for
  for(int i = 0; i < N; ++i){
    x = (double)rand()/RAND_MAX;
    y = (double)rand()/RAND_MAX;

    if(x*x + y*y <= LENGTH) ++count_in;
    ++count_all;
  }

  fprintf(stdout, "pi : %lf\n", (double)(count_in << 2)/count_all);

  return 0;
}
