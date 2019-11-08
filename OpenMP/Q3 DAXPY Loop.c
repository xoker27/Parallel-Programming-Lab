#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
# define m 10
# define n 8

int main() {
    int a[m],b[m],p;
    clock_t s,e,s1,e1;
    for(int i = 0; i<m ;i++){
        a[i] = rand() % 1000;
    }

    for(int i = 0; i<m ;i++){
        b[i] = rand() % 1000;
    }
    s1=clock();
    for(int i = 1; i<m; i=i+n)
        a[i] = a[i] * p + b[i];
    e1= clock();
    p= 1;
    s=clock();
    # pragma omp parallel
    {
        omp_set_num_threads(n);
        int id ;
        id = omp_get_thread_num();
        for(int i = id; i<m; i=i+n)
            a[i] = a[i] * p + b[i];
    }
    e= clock();
    double ex = ((double)(e-s))/CLOCKS_PER_SEC;
    double ex1 = ((double)(e1-s1))/CLOCKS_PER_SEC;
    for (int j =0;j<m;j++)
        printf("%d\t", a[j]);
    printf("%f", ex1/ex);

}
