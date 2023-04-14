## Blocking and Nonblocking

### Deadlocks

A deadlock may occur when a program is indefinately waiting for a message that was never sent. 

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/deadlockcropped.png)

##### In python

```
import numpy
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()

randNum = numpy.zeros(1)

if rank == 0:
    comm.Recv(randNum, source=1)

if rank == 1:
    comm.Recv(randNum, source=0)

```

##### In C

```
#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    double randNum = 0.0;
    MPI_Status status;

    if (rank == 0) {
        MPI_Recv(&randNum, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &status);
    }

    if (rank == 1) {
        MPI_Recv(&randNum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
    }

    printf("Process %d received the number %f\n", rank, randNum);

    MPI_Finalize();
    return 0;
}


```
##### Output

This code will not produce any output and keep waiting. This is because Recv and Send are blocking calls. The program will not move ahead till it has received the message. A simple fix to this would be to use non-blocking calls like Irecv and Isend. 

##### In python

```
import numpy
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()

randNum = numpy.zeros(1)

if rank == 0:
    print("Process", rank, "before receiving has the number", randNum[0])
    comm.Irecv(randNum, source=1)
    print("Process", rank, "received the number", randNum[0])

if rank == 1:
    print("Process", rank, "before receiving has the number", randNum[0])
    comm.Irecv(randNum, source=0)
    print("Process", rank, "received the number", randNum[0])

```
##### In C

```
#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    double randNum = 0.0;
    MPI_Status status;

    if (rank == 0) {
        printf("Process %d before receiving has the number %f\n", rank, randNum);
        MPI_Request request;
        MPI_Irecv(&randNum, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        printf("Process %d received the number %f\n", rank, randNum);
    }

    if (rank == 1) {
        printf("Process %d before receiving has the number %f\n", rank, randNum);
        MPI_Request request;
        MPI_Irecv(&randNum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        printf("Process %d received the number %f\n", rank, randNum);
    }

    MPI_Finalize();
    return 0;
}

```
##### Output

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output4.jpg)

### Non-Blocking Communication

The `Irecv` and `Isend` methods are non-blocking call i.e. they return a `Request` which can then be either tested, waited on or cancelled.

`Request.Wait()`: blocks the calling process 

`Request.Test()`: return true if completed

`Request.Cancel()`: cancels communication

#### Code example: Overlapping Communication and Computation

##### In Python
```
from mpi4py import MPI
import numpy

comm = MPI.COMM_WORLD
rank = comm.rank

randNum = numpy.zeros(1)

# send a message from rank 0 to rank 1 using non-blocking communication
if rank == 0:
    randNum = numpy.random.random_sample(1)
    req = comm.Isend(randNum, dest=1)
    print("Rank {} sent data: {}".format(rank, randNum))
elif rank == 1:
    req = comm.Irecv(randNum,source=0)
    
# do some other computation while waiting for communication to complete
print("Rank {} is doing some other computation...".format(rank))
result = 0
for i in range(10000000):
    result += i

# wait for the communication to complete
req.Wait()

# print the received message
if rank == 1:
    print("Rank {} received data: {}".format(rank, randNum))
````

##### In C
The functions used for Non-Blocking communication MPI_Isend(), MPI_Irecv(), and MPI_Wait():

`MPI_Isend()`: non-blocking send operation

##### int MPI_Isend(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
- buf: address of send buffer
- count: number of elements to send
- datatype: datatype of each element
- dest: rank of destination process
- tag: message tag
- comm: communicator
- request: pointer to communication request object

`MPI_Irecv()`: non-blocking receive operation

##### int MPI_Irecv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request)
- buf: address of receive buffer
- count: maximum number of elements to receive
- datatype: datatype of each element
- source: rank of source process
- tag: message tag
- comm: communicator
- request: pointer to communication request object

`MPI_Wait()`: wait for a communication to complete

##### int MPI_Wait(MPI_Request *request, MPI_Status *status)
- request: pointer to communication request object
- status: pointer to status object (may be MPI_STATUS_IGNORE if status information is not needed)

```
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double randNum = 0.0;
    MPI_Request req;
    MPI_Status status;

    // send a message from rank 0 to rank 1 using non-blocking communication
    if (rank == 0) {
        randNum = (double) rand() / RAND_MAX;
        MPI_Isend(&randNum, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &req);
        printf("Rank %d sent data: %f\n", rank, randNum);
    } else if (rank == 1) {
        MPI_Irecv(&randNum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &req);
    }

    // do some other computation while waiting for communication to complete
    printf("Rank %d is doing some other computation...\n", rank);
    double result = 0.0;
    for (int i = 0; i < 10000000; i++) {
        result += i;
    }

    // wait for the communication to complete
    MPI_Wait(&req, &status);

    // print the received message
    if (rank == 1) {
        printf("Rank %d received data: %f\n", rank, randNum);
    }

    MPI_Finalize();
    return 0;
}


```

##### Output

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output5.jpg)

[Next Section](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/Broadcast.md)

### References

Spagnuolo, C. (2020). Coding games and programming challenges to code better. CodinGame. Retrieved April 12, 2023, from https://www.codingame.com/playgrounds/47058/have-fun-with-mpi-in-c/lets-start-to-have-fun-with-mpi 

Watson, G. (2017). Introduction. Python MPI: Introduction. Retrieved April 12, 2023, from https://nyu-cds.github.io/python-mpi/01-introduction/ 







