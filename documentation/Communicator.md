## MPI Communicator

In MPI (Message Passing Interface), a communicator object defines a group of processes that can communicate with each other. `COMM_WORLD` is the default global communicator which refers to all the processes launched at the start of the program.

The communicator object contains the `Rank` and `Size` among other information. `Rank` is the unique ID of each process that starts from 0 and go till n-1 whereas `Size` is n which is the total number of process.

#### Code Example: Hello World in MPI

##### In Python

```
from mpi4py import MPI

comm = MPI.COMM_WORLD # Access the world communicator object
rank = comm.rank # Get the rank of the current process
size = comm.size # Get the total number of processes

print('Hello from process', rank, ' of ', size)
```

##### In C

```
#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv); // Initialize MPI environment
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the current process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processes

    printf("Hello from process %d of %d\n", rank, size);

    MPI_Finalize(); // Finalize MPI environment
    return 0;
}
```

##### Output

For two processes output should look like:

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output1.jpg)

### References

Dalcin, L. (2023). MPI for python. MPI for Python - MPI for Python 3.1.4 documentation. Retrieved April 13, 2023, from https://mpi4py.readthedocs.io/ 
