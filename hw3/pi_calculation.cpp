#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
 
int main(int argc, char *argv[]) 
{
  int n1 = 2030000000, n2 = 0;
  float a, b, m, pi;
  double start, end;
  int my_thread_id;
  unsigned int seed;

  start = omp_get_wtime();
#pragma omp parallel for private(i, seed, my_thread_id, a, b, m) shared(n1) reduction(+:n2)
  for (int i = 1; i <= n1; i++) {
      my_thread_id = omp_get_thread_num();
      unsigned int seed = (unsigned) 123 * my_thread_id + i;
      a = (float)rand_r(&seed) / RAND_MAX;
      b = (float)rand_r(&seed) / RAND_MAX;
      m = a * a + b * b;
      if (m <= 1) {
      	n2++;
      }
  }
 
  pi = (float)4 * n2 / n1;
  end = omp_get_wtime();
  printf("Time consumption - %f\n", (end - start));
  printf("Total number of points = %i, Number of points inside circle=%i, Pi = %f\n", n1, n2, pi);  
  return 0;
}
