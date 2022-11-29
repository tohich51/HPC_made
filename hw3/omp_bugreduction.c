#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

float dotprod(float * a, float * b, size_t N)
{
    int i, tid;
    float sum = 0.0;

#pragma omp parallel for reduction(+:sum)
    for (i = 0; i < N; ++i)
    {
        sum += a[i] * b[i];
        tid = omp_get_thread_num();	
        printf("tid = %d i = %d sum= %f \n", tid, i, sum);
    }

    return sum;
}

int main (int argc, char *argv[])
{
    const size_t N = 10;
    int i;
    float sum;
    float a[N], b[N];
    omp_set_num_threads(3);

    for (i = 0; i < N; ++i)
    {
        a[i] = b[i] = (double)i;
    }

    sum = dotprod(a, b, N);

    printf("Sum = %f\n",sum);

    return 0;
}
