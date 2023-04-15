## Broadcast

In this one process sends out data to all other processes.

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/5.png)

Both the sender process and receiver processes call the function `Comm.Bcast`. Sender sends and receives the data whereas the receiver processes just receive.

#### Code Example: Broadcasting

##### In Python

###### Comm.Bcast(obj, root=0)
- Comm: Communicator
- obj: Data we wish to send/receive
- root (int): Sender Process Rank

```
from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.rank

if (rank == 0):
    data = 1000
else:
    data = None

# all processes will get the variable data from process 0
data = comm.bcast(data, root=0)

print("Process", rank, "has data", data)

```

##### In C

###### int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)

- buffer: pointer to the buffer holding the data to be broadcasted (send buffer for the root process, receive buffer for all other processes)
- count: number of data elements to be broadcasted
- datatype: data type of the broadcasted data
- root: rank of the root process (the process that sends the data)
- comm: communicator that defines the scope of the broadcast operation

```
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
```

##### Output

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output6.jpg)


[Next Section](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/ScatterandGather.md)

### References

Diaz, J., Munoz-Caro, C., & Nino, A. (2012). A survey of parallel programming models and tools in the multi and many-core era. IEEE Transactions on parallel and distributed systems, 23(8), 1369-1386

Spagnuolo, C. (2020). Coding games and programming challenges to code better. CodinGame. Retrieved April 12, 2023, from https://www.codingame.com/playgrounds/47058/have-fun-with-mpi-in-c/lets-start-to-have-fun-with-mpi 

Watson, G. (2017). Introduction. Python MPI: Introduction. Retrieved April 12, 2023, from https://nyu-cds.github.io/python-mpi/01-introduction/ 
