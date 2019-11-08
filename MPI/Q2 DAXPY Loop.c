#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX 65536


int main(int argc, char* argv[]) {
    int rank, size;
    int X[MAX], Y[MAX];
    int a = rand()%32767;
	for (int i = 0; i < MAX; i++){
        X[i] = rand()%32767;
        Y[i] = rand()%32767;
    }
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //printf("Rank: %d is active now!\n",rank);
    
    MPI_Barrier(MPI_COMM_WORLD);
    double startTime = MPI_Wtime();
    for (int i = rank; i < MAX; i+=size) {
        X[i] = a*X[i] + Y[i];
    }
    MPI_Barrier(MPI_COMM_WORLD);
    double endTime = MPI_Wtime();
   
    if (rank == 0){
    	for (int i = 0; i < MAX; i++){
		    printf("%d ",X[i]);
        }
        printf("\nTime taken for multiprocessor calculation: %lf ms\n", (endTime-startTime)*(1000));
    } 

    MPI_Finalize();

    return 0;
}
