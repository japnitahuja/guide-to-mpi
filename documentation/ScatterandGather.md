## Scatter and Gather

### Scatter

Scatter sends data from one processes to all processes much like broadcast however, it divides the data into smaller pieces and equally distributes it.

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/6.png)

#### Code Example: Scattering

##### In Python

###### Comm.Scatter(sendobj, root=0)
- sendobj: data to be scattered
- root: process that will scatter

```
from mpi4py import MPI
import numpy as np

comm = MPI.COMM_WORLD
rank = comm.rank
size = comm.size

if rank == 0:
    data = np.arange(1, size + 1)
else:
    data = None

# Scatter the data array to all processes
data = comm.scatter(data, root=0)
print("Process", rank, "has received ", data)
```

#### In C
 
##### int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)

- sendbuf: A pointer to the send buffer, which contains the data to be scattered. This argument is significant only at the root process (i.e., the process with rank root).
- sendcount: The number of elements to be sent to each process. This argument is significant only at the root process.
- sendtype: The MPI data type of the elements in the send buffer.
- recvbuf: A pointer to the receive buffer, where the data is stored on the non-root processes after scattering. This buffer should be large enough to hold the data received by each process.
- recvcount: The number of elements in the receive buffer for each process.
- recvtype: The MPI data type of the elements in the receive buffer.
- root: The rank of the root process, i.e., the process from which the data is being scattered.
- comm: The communicator over which the scattering operation is performed.
```#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *data = NULL;
    if (rank == 0) {
        data = (int *)malloc(size * sizeof(int));
        for (int i = 0; i < size; i++) {
            data[i] = i + 1;
        }
    }

    int local_data;
    MPI_Scatter(data, 1, MPI_INT, &local_data, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Process %d has received %d\n", rank, local_data);

    if (data != NULL) {
        free(data);
    }

    MPI_Finalize();
    return 0;
}
```


##### Output

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output7.jpg)

### Gather

Gather does the opposite of scatter. It gets data from each process, combines it into an array and sends it to the root process.

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/7.png)

#### Code Example: Scattering and Gathering

This program scatters an array, performs a computation on the number it received (here it is adding 10) and then sends it back to be gathered.

##### In Python

###### Comm.Gather(sendobj, root=0)
- sendobj: data to be gathered
- root: process that will gather

```
from mpi4py import MPI
import numpy as np

comm = MPI.COMM_WORLD
rank = comm.rank
size = comm.size

if rank == 0:
    data = np.arange(1, size + 1)
else:
    data = None

# Scatter the data array to all processes
data = comm.scatter(data, root=0)
print("Process", rank, "has received ", data)
data += 10

data = comm.gather(data, root=0)

# Print the result on the root process
if rank == 0:
    print("The gathered result is", data)

```
##### int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
- sendbuf: A pointer to the send buffer, which contains the data to be gathered. This argument is significant only at the non-root processes (i.e., processes other than the root process).
- sendcount: The number of elements to be sent from each process. This argument is significant only at the non-root processes.
- sendtype: The MPI data type of the elements in the send buffer.
- recvbuf: A pointer to the receive buffer, where the gathered data is stored on the root process. This buffer should be large enough to hold the data received from all processes.
- recvcount: The number of elements in the receive buffer for the root process.
- recvtype: The MPI data type of the elements in the receive buffer.
- root: The rank of the root process, i.e., the process to which the data is being gathered.
- comm: The communicator over which the gather operation is performed.

##### In C
```#include <stdio.h>
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
```

##### Output

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output8.jpg)

### Scatter and Gather

`Scatter` allows the root process to distribute the data among all the processes in the communicator. The data is divided into equal-sized chunks and each process receives one of these chunks. `Gather` is the reverse operation of scatter. It allows all processes to send their local data to the root process, which collects all the data and stores it in a single array.

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/10.png)


[Next Section](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/ScatterandReduce.md)

### References

Diaz, J., Munoz-Caro, C., & Nino, A. (2012). A survey of parallel programming models and tools in the multi and many-core era. IEEE Transactions on parallel and distributed systems, 23(8), 1369-1386

Spagnuolo, C. (2020). Coding games and programming challenges to code better. CodinGame. Retrieved April 12, 2023, from https://www.codingame.com/playgrounds/47058/have-fun-with-mpi-in-c/lets-start-to-have-fun-with-mpi 

Watson, G. (2017). Introduction. Python MPI: Introduction. Retrieved April 12, 2023, from https://nyu-cds.github.io/python-mpi/01-introduction/ 
