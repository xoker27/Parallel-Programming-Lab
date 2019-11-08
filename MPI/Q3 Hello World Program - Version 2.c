#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define RECEIVER 0
#define BUFFER_SIZE 20
#define TAG 42

char MESSAGE[] = "Hello World!";

int main(int argc, char* argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if(rank == RECEIVER) {
        printf("RECEIVER with rank %d waiting for messages\n", RECEIVER);
        char MESSAGE[BUFFER_SIZE];
        for (int i = 1; i < size; i++) {
            MPI_Recv(MESSAGE, BUFFER_SIZE, MPI_CHAR, MPI_ANY_SOURCE, TAG, MPI_COMM_WORLD, &status);
            int source = status.MPI_SOURCE;
            printf("Received message \"%s\" from process %d\n", MESSAGE, source);
        }
    }
    else {
        MPI_Send(MESSAGE, BUFFER_SIZE, MPI_CHAR, RECEIVER, TAG, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
