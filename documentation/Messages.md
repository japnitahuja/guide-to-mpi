## Sending and Receiving Messages

#### Code Example: Sending and Receiving Data

##### In Python

```
from mpi4py import MPI

comm = MPI.COMM_WORLD  # accessing the communicator object
rank = comm.rank  # getting the rank of the current process

shared = rank+100

if(rank == 0):
    data = shared
    comm.send(data, dest=1)  # sending data to process with rank of dest
    print("From process", rank, "we sent", data)
elif(rank == 1):
    # receiving data from process with rank of source
    data = comm.recv(source=0)
    print("On process", rank, "we received", data)
```

##### In C

##### Output

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output3.jpg)
