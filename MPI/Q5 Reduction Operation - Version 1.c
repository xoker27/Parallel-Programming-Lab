#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MASTER 0
#define TAG 42

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int count = 0;
    srand(time(NULL)^rank);
    
    int num = rand()%20;
    printf("Processor %d with number %d created!\n", rank, num);

    MPI_Barrier(MPI_COMM_WORLD);

    while (size > 1) {
        if(size%2!=0) {
            if(rank == 0) {
                int x;
                MPI_Recv(&x, 1, MPI_INTEGER, size/2, TAG, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
                num+=x;
            }
            if(rank == size/2 ) {
                MPI_Send(&num, 1, MPI_INTEGER, 0, TAG, MPI_COMM_WORLD);
            }
            
            for (int i = 0; i < size/2; i++) {
                if(rank == i) {
                    int x;
                    MPI_Recv(&x, 1, MPI_INTEGER, i + size/2 + 1, TAG, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
                    num+=x;
                }
                if(rank == i + size/2 + 1) {
                    MPI_Send(&num, 1, MPI_INTEGER, i, TAG, MPI_COMM_WORLD);
                }
            }
        }
        else {
            for (int i = 0; i < size/2; i++) {
                if(rank == i) {
                    int x;
                    MPI_Recv(&x, 1, MPI_INTEGER, i + size/2, TAG, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
                    num+=x;
                }
                if(rank == i + size/2) {
                    MPI_Send(&num, 1, MPI_INTEGER, i, TAG, MPI_COMM_WORLD);
                }
            }
        }

        size/=2;

    }

    if(rank == MASTER)
        printf("\nArray Sum: %d\n", num);

    MPI_Finalize();
    return 0;
}
