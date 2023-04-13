## Scatter and Reduce

### Reduce

In a reduction function, all inputs are combined or reduced to give a singular output.

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/reduce.jpg)

#### Code Example: Broadcasting and Reduce

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

if rank == 0:
    data = np.arange(1, size + 1)
else:
    data = None

# broadcast the data array to all processes
data = comm.bcast(data, root=0)
print("Process", rank, "has received ", data)

# Reduce the local sum to obtain the global sum
global_sum = comm.reduce(data, op=MPI.SUM, root=0)

# Print the result on the root process
if rank == 0:
    print("The sum of the array is", global_sum)
```


[Next Section](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/Communicator.md)

### References

Diaz, J., Munoz-Caro, C., & Nino, A. (2012). A survey of parallel programming models and tools in the multi and many-core era. IEEE Transactions on parallel and distributed systems, 23(8), 1369-1386

Spagnuolo, C. (2020). Coding games and programming challenges to code better. CodinGame. Retrieved April 12, 2023, from https://www.codingame.com/playgrounds/47058/have-fun-with-mpi-in-c/lets-start-to-have-fun-with-mpi 

Watson, G. (2017). Introduction. Python MPI: Introduction. Retrieved April 12, 2023, from https://nyu-cds.github.io/python-mpi/01-introduction/ 
