#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 16

int main(int argc, char **argv) {
    int rank, size;
    int i, *sendbuf, *recvbuf;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 4) {
        fprintf(stderr, "This program is designed to run with 4 processes.\n");
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    if (rank == 0) {
        // Create an array of integers to be scattered
        sendbuf = (int *) malloc(ARRAY_SIZE * sizeof(int));
        for (i = 0; i < ARRAY_SIZE; i++) {
            sendbuf[i] = i;
        }
    }

    // Create a receive buffer for each process
    recvbuf = (int *) malloc(ARRAY_SIZE / size * sizeof(int));

    // Scatter the array from process 0 to all processes
    MPI_Scatter(sendbuf, ARRAY_SIZE / size, MPI_INT, recvbuf, ARRAY_SIZE / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Print the local array on each process
    printf("Rank %d received: ", rank);
    for (i = 0; i < ARRAY_SIZE / size; i++) {
        printf("%d ", recvbuf[i]);
    }
    printf("\n");

    // Gather the arrays from all processes onto process 0
    MPI_Gather(recvbuf, ARRAY_SIZE / size, MPI_INT, sendbuf, ARRAY_SIZE / size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Print the final array on process 0
        printf("Final array: ");
        for (i = 0; i < ARRAY_SIZE; i++) {
            printf("%d ", sendbuf[i]);
        }
        printf("\n");

        free(sendbuf);
    }

    free(recvbuf);
    MPI_Finalize();

    return EXIT_SUCCESS;
}
