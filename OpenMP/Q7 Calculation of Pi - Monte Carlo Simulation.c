#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>
#define SEED 35791246

static long num_trials = 100000;

int main () {
    long i ,ncirc =0;
    double pi,x,y,z;
    srand(SEED);
    #pragma omp parallel for private (x,y) reduction (+:ncirc)
    for (i=0;i<num_trials;i++) {
        x = (double)rand()/RAND_MAX;
        y = (double)rand()/RAND_MAX;
        z= x*x+y*y;
        if (z<=1)
            ncirc++;
    }

    pi= 4.0 * ((double)ncirc / (double) num_trials);
    printf("\n %ld trails , pi is %f \n", num_trials, pi);
}
