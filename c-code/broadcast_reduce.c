#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int root = 0;
    int data = 0;
    int sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Broadcast data from root process to all other processes
    MPI_Bcast(&data, 1, MPI_INT, root, MPI_COMM_WORLD);
    printf("Process %d received broadcast data: %d\n", rank, data);

    // Perform reduction operation on data from all processes
    MPI_Reduce(&data, &sum, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
    if (rank == root) {
        printf("Sum of all data: %d\n", sum);
    }

    MPI_Finalize();
    return 0;
}
