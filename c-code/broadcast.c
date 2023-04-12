#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int data = 42;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Broadcast data from root process to all other processes
        MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    } else {
        // Receive data broadcasted from root process
        MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);
        printf("Process %d received data: %d\n", rank, data);
    }

    MPI_Finalize();
    return 0;
}
