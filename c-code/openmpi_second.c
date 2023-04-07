#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, i, n = 100;
    int *data = NULL, *subdata = NULL, local_sum = 0, global_sum = 0;

    MPI_Init(&argc, &argv); // Initialize MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the current process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processes

    // Allocate memory for the data array
    if (rank == 0) {
        data = (int*) malloc(n * sizeof(int));
        for (i = 0; i < n; i++) {
            data[i] = i + 1;
        }
    }

    // Scatter the data array to all processes
    subdata = (int*) malloc(n / size * sizeof(int));
    MPI_Scatter(data, n / size, MPI_INT, subdata, n / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Compute the local sum of the subdata array
    for (i = 0; i < n / size; i++) {
        local_sum += subdata[i];
    }

    // Reduce the local sum to obtain the global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print the result on the root process
    if (rank == 0) {
        printf("The sum of the array is %d\n", global_sum);
        free(data);
    }
    free(subdata);

    MPI_Finalize(); // Finalize MPI environment
    return 0;
}
