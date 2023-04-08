## Sending and Receiving Messages

Processes communicate with each other by sending and receiving messages.

#### Code Example: Sending and Receiving Data

##### In Python

```
from mpi4py import MPI

comm = MPI.COMM_WORLD  # accessing the communicator object
rank = comm.rank  # getting the rank of the current process

if(rank == 0):
    data = rank+100
    comm.send(data, dest=1)  # sending data to process with rank of dest
    print("From process", rank, "we sent", data)
elif(rank == 1):
    # receiving data from process with rank of source
    data = comm.recv(source=0)
    print("On process", rank, "we received", data)
```

##### In C

```
#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int shared = rank + 100;

    if (rank == 0)
    {
        int data = shared;
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("From process %d we sent %d\n", rank, data);
    }
    else if (rank == 1)
    {
        int data;
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("On process %d we received %d\n", rank, data);
    }

    MPI_Finalize();
    return 0;
}
```

##### Output

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output3.jpg)
