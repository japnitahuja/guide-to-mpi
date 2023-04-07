#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, i, n = 100;
    int *x = NULL, *y = NULL, *subx = NULL, *suby = NULL;
    int local_dot = 0, global_dot = 0;

    MPI_Init(&argc, &argv); // Initialize MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the current process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processes

    // Allocate memory for the arrays
    if (rank == 0) {
        x = (int*) malloc(n * sizeof(int));
        y = (int*) malloc(n * sizeof(int));
        for (i = 0; i < n; i++) {
            x[i] = i + 1;
            y[i] = n - i;
        }
    }

    // Scatter the arrays to all processes
    subx = (int*) malloc(n / size * sizeof(int));
    suby = (int*) malloc(n / size * sizeof(int));
    MPI_Scatter(x, n / size, MPI_INT, subx, n / size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(y, n / size, MPI_INT, suby, n / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Compute the local dot product of the subarrays
    for (i = 0; i < n / size; i++) {
        local_dot += subx[i] * suby[i];
    }

    // Reduce the local dot products to obtain the global dot product
    MPI_Reduce(&local_dot, &global_dot, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print the result on the root process
    if (rank == 0) {
        printf("The dot product of the arrays is %d\n", global_dot);
        free(x);
        free(y);
    }
    free(subx);
    free(suby);

    MPI_Finalize(); // Finalize MPI environment
    return 0;
}
