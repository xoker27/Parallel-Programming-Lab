#include "omp.h"
#include "stdio.h"

void printHello(int threadID) {
	printf("hello(%d)", threadID);
    printf("world(%d) \n", threadID);
}
void main(){
    /* Parallel region begins here */
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        printHello(ID);
    }
}
