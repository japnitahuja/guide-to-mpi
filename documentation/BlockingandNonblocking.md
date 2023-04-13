## Blocking and Nonblocking

### Deadlocks

A deadlock may occur when a program is indefinately waiting for a message that was never sent. 

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/deadlock.jpg)

#### In python

```
import numpy
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()

randNum = numpy.zeros(1)

if rank == 1:
        randNum = numpy.random.random_sample(1)
        print("Process", rank, "drew the number", randNum[0])
        #comm.Send(randNum, dest=0) #sending the message is commented out

if rank == 0:
        print("Process", rank, "before receiving has the number", randNum[0])
        comm.Recv(randNum, source=1)
        print("Process", rank, "received the number", randNum[0])
```

#### In C

#### Output

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output4.jpg)

This is because Recv and Send are blocking calls. The program will not move ahead till it has received the message. A simple fix to this would be to use non-blocking calls like Irecv and Isend. 

#### In python
```
import numpy
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()

randNum = numpy.zeros(1)

if rank == 1:
        randNum = numpy.random.random_sample(1)
        print("Process", rank, "drew the number", randNum[0])
        #comm.Send(randNum, dest=0)

if rank == 0:
        print("Process", rank, "before receiving has the number", randNum[0])
        comm.Irecv(randNum, source=1)
        print("Process", rank, "received the number", randNum[0])
```
#### In C

#### Output

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output5.jpg)





