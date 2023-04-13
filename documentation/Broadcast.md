## Broadcast

In this one process sends out data to all other processes.

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/broadcast.jpg)

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

##### Output

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output6.jpg)


[Next Section]()

### References

Diaz, J., Munoz-Caro, C., & Nino, A. (2012). A survey of parallel programming models and tools in the multi and many-core era. IEEE Transactions on parallel and distributed systems, 23(8), 1369-1386

Spagnuolo, C. (2020). Coding games and programming challenges to code better. CodinGame. Retrieved April 12, 2023, from https://www.codingame.com/playgrounds/47058/have-fun-with-mpi-in-c/lets-start-to-have-fun-with-mpi 

Watson, G. (2017). Introduction. Python MPI: Introduction. Retrieved April 12, 2023, from https://nyu-cds.github.io/python-mpi/01-introduction/ 
