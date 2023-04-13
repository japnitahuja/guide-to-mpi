#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double randNum;

    if (rank == 1) {
        srand(time(NULL));
        randNum = (double)rand() / (double)RAND_MAX;
        printf("Process %d drew the number %f\n", rank, randNum);
       // MPI_Send(&randNum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        printf("Process %d before receiving has the number %f\n", rank, randNum);
        MPI_Recv(&randNum, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received the number %f\n", rank, randNum);
    }

    MPI_Finalize();
    return 0;
}
