#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double randNum = 0.0;
    MPI_Request req;
    MPI_Status status;
    if (rank == 0) {
        randNum = (double)rand() / (double)RAND_MAX;
        MPI_Isend(&randNum, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &req);
        printf("Rank %d sent data: %f\n", rank, randNum);
    } else if (rank == 1) {
        MPI_Irecv(&randNum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &req);
    }
    
    // do some other computation while waiting for communication to complete
    printf("Rank %d is doing some other computation...\n", rank);
    double result = 0.0;
    for (int i = 0; i < 10000000; i++) {
        result += i;
    }
    
    MPI_Wait(&req, &status);
    
    if (rank == 1) {
        printf("Rank %d received data: %f\n", rank, randNum);
    }
    
    MPI_Finalize();
    return 0;
}
