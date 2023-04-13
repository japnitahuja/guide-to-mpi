## Blocking and Nonblocking

### Deadlocks

A deadlock may occur when a program is indefinately waiting for a message that was never sent. 

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/deadlock.jpg)

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

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/deadlock.png)
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
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double randNum = 0.0;

    if (rank == 1) {
        srand(time(NULL));
        randNum = (double) rand() / (double) RAND_MAX;
        printf("Process %d drew the number %f\n", rank, randNum);
        // MPI_Send(&randNum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        printf("Process %d before receiving has the number %f\n", rank, randNum);
        MPI_Request request;
        MPI_Irecv(&randNum, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &request);
        MPI_Status status;
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

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/nonblock.png)

##### Output

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output5.jpg)







