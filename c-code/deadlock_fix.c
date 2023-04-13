
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    double randNum = 0.0;

    if(rank == 0){
        printf("Process %d before receiving has the number %f\n", rank, randNum);
        MPI_Request request;
        MPI_Irecv(&randNum, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        printf("Process %d received the number %f\n", rank, randNum);
    }

    if(rank == 1){
        printf("Process %d before receiving has the number %f\n", rank, randNum);
        MPI_Request request;
        MPI_Irecv(&randNum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        printf("Process %d received the number %f\n", rank, randNum);
    }

    MPI_Finalize();
    return 0;
}
