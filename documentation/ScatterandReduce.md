## Scatter and Reduce

### Reduce

In a reduction function, all inputs are combined or reduced to give a singular output. It differs from gather since it reduces it to one value through some aggregation function.

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/8.png)

#### Code Example: Global Sum

 It first initializes MPI and divides an array of integers from 1 to n into size chunks using numpy. The scatter function is then called to send the appropriate chunk of data to each process. Each process receives its own chunk of data and computes the sum of its local chunk using the numpy sum function. Finally, the local sums are combined into a global sum using the reduce function with the MPI.SUM operator, and the root process prints the result.

##### In Python

###### Comm.Reduce(sendbuf, recvbuf, op=SUM, root=0)
- sendbuf: The data that the current process wants to send to other processes
- recvbuf: The result of the reduction operation
- op: Reduction operation: SUM, MAX, MIN, PRODUCT or Custom
- root: The process that will receive the result

```
from mpi4py import MPI
import numpy as np

comm = MPI.COMM_WORLD
rank = comm.rank
size = comm.size
n = 2 * size

if rank == 0:
    data = np.arange(1, n+1)
    chunks = [[] for i in range(size)]
    # data needs to be divided in chunks manually for scatter
    for i in range(size):
        for j in range(n//size):
            chunks[i].append(data[i*(n//size)+j])
else:
    data = None
    chunks = None

# Scatter the data array to all processes
chunks = comm.scatter(chunks, root=0)
print("Process", rank, "has received ", chunks)

# Compute the local sum of the subdata array
local_sum = np.sum(chunks)

# Reduce the local sum to obtain the global sum
global_sum = comm.reduce(local_sum, op=MPI.SUM, root=0)

# Print the result on the root process
if rank == 0:
    print("The sum of the array is", global_sum)


```

##### In C
###### int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)
- sendbuf: pointer to the send buffer, which contains the data to be reduced on each process. On the root process, this argument is ignored.
- recvbuf: pointer to the receive buffer, which will hold the result of the reduction operation on the root process.
- count: number of data elements in the send buffer.
- datatype: data type of the data elements in the send buffer.
- op: reduction operation to be performed. This is a predefined reduction operation such as MPI_SUM, MPI_MAX, etc.
- root: rank of the root process, which will receive the result of the reduction operation.
- comm: communicator that defines the group of processes involved in the reduction operation.
```
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

```

##### Output

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output9.jpg)

#### Code Example: Global Dot

 It first initializes the MPI communicator, gets the rank and size. The total length of the arrays is defined as n which is twice the size of the communicator. Then on process rank 0, two arrays x and y are created using NumPy's arange() function. These arrays are then manually divided into sub-arrays and distributed among all processes using the scatter() function. Each process computes the dot product of its local sub-arrays and then sends the result to process rank 0 using the reduce() function to obtain the final dot product. The result is then printed on process rank 0.

##### In Python

```
from mpi4py import MPI
import numpy as np

comm = MPI.COMM_WORLD
rank = comm.rank
size = comm.size
n = 2 * size

if rank == 0:
    x = np.arange(1, n+1)
    y = np.arange(1, n+1)
    chunks_x = [[] for i in range(size)]
    chunks_y = [[] for i in range(size)]
    # data needs to be divided in chunks manually for scatter
    for i in range(size):
        for j in range(n//size):
            chunks_x[i].append(x[i*(n//size)+j])
            chunks_y[i].append(y[i*(n//size)+j])
else:
    x = None
    y = None
    chunks_x = None
    chunks_y = None

# Scatter the data array to all processes
chunks_x = comm.scatter(chunks_x, root=0)
chunks_y = comm.scatter(chunks_y, root=0)
print("Process", rank, "has received ", chunks_x, "and", chunks_y)

# Compute the local sum of the subdata array
local_dot = sum([chunks_x[i] * chunks_y[i] for i in range(len(chunks_x))])

# Reduce the local sum to obtain the global sum
global_dot = comm.reduce(local_dot, op=MPI.SUM, root=0)

# Print the result on the root process
if rank == 0:
    print("The sum of the array is", global_dot)

```

##### In C
```#include <stdio.h>
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
```

##### Output

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output10.jpg)

### Scatter and Reduce

`Scatter` is an operation in which an array is divided into smaller chunks and each process receives a portion of the array. `Reduce` is an operation that combines the values on each process into a single value. 

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/9.png)

[Next Section](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/Hybrid.md)

### References

Diaz, J., Munoz-Caro, C., & Nino, A. (2012). A survey of parallel programming models and tools in the multi and many-core era. IEEE Transactions on parallel and distributed systems, 23(8), 1369-1386

Spagnuolo, C. (2020). Coding games and programming challenges to code better. CodinGame. Retrieved April 12, 2023, from https://www.codingame.com/playgrounds/47058/have-fun-with-mpi-in-c/lets-start-to-have-fun-with-mpi 

Watson, G. (2017). Introduction. Python MPI: Introduction. Retrieved April 12, 2023, from https://nyu-cds.github.io/python-mpi/01-introduction/ 
