#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>

static long numsteps = 100000;
double step;

#define n 2

void main(){
    double pi=0.0,x,sum=0.0;
    clock_t s,e;
    int nthreads,i, id;
    step = 1.0/ (double)numsteps;
    omp_set_num_threads (n);
    s=clock();
    #pragma omp parallel for private(x) reduction (+:sum)

    for (i= id;i<numsteps;i++) {
        x= (i+0.5)*step;
        sum+= 4.0/(1.0+x*x);
    }

    pi+= sum* step;

    e= clock();
    double ex = ((double)(e-s))/CLOCKS_PER_SEC;
    printf("%f\n",pi);
    printf("%f", ex);
}
