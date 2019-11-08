#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
#define m 10
#define n 4

int main() {
    int a[m][m],b[m][m],c[m][m],i,j,k;
    clock_t s,e;
    for(int i = 0; i<m ;i++){
        for(int j= 0;j<m;j++){
            a[i][j] = rand() % 2;
            b[i][j] = rand() % 2;
        }
    }
    s=clock();
    # pragma omp parallel private (i,j, k)
    {
        for(i = 0; i < m; i++) {
                for (j = 0; j < m; j++) {
                    c[i][j] = 0;
                    for (k = 0; k < m; k++)
                        c[i][j] += a[i][k]*b[k][j];
            }
        }
    }
    e= clock();
    double ex = ((double)(e-s))/CLOCKS_PER_SEC;

    for(int i = 0; i<m ;i++){
        for(int j= 0;j<m;j++) {
            printf("%d \t", c[i][j]);
        }
        printf("\n");
    }
    printf("%f", ex);
}
