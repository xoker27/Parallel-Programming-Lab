#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>

static long numsteps = 100000;
double step;

#define n 2

void main() {
    double pi=0.0;
    clock_t s,e;
    int nthreads;
    step = 1.0/ (double)numsteps;
    omp_set_num_threads (n);
    s=clock();
    #pragma omp parallel
    {
        int i, id, nth;
        double x, sum;
        id = omp_get_thread_num ();
        nth = omp_get_num_threads();
        if (id==0)
        nthreads= nth;
        for (i= id, sum=0.0;i<numsteps;i+= nthreads) {
            x= (i+0.5)*step;
            sum+= 4.0/(1.0+x*x);
        }
        # pragma omp critical
        pi+= sum* step;
    }
    e= clock();
    double ex = ((double)(e-s))/CLOCKS_PER_SEC;
    printf("%f\n",pi);
    printf("%f", ex);
}
