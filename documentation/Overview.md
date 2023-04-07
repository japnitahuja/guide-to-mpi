## Overview

### What is MPI?

MPI or message passing interface is the agreed upon standard to support parallel programming in distributed system. Processes communicate via messages which can refer to raw data, signals or acknowledgements.

### Why MPI?

### How does MPI work?

MPI launches a user specified number of processes at the start of the program. Usually, this is the number of cores in a system. The processes have their own memory and do not share it with other processes.

Each process has a unique `Rank` associated with it. This value is used to differentiate between the processes in the code.

#### MPI Communicator

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

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output1.jpg)
