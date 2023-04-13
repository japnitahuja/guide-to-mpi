## Scatter and Reduce

### Reduce

In a reduction function, all inputs are combined or reduced to give a singular output. It differs from gather since it reduces it to one value through some aggregation function.

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/reduce.jpg)

#### Code Example: Global Sum

 It first initializes MPI and divides an array of integers from 1 to n into size chunks using numpy. The scatter function is then called to send the appropriate chunk of data to each process. Each process receives its own chunk of data and computes the sum of its local chunk using the numpy sum function. Finally, the local sums are combined into a global sum using the reduce function with the MPI.SUM operator, and the root process prints the result.

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
n = 2 * size

if rank == 0:
    data = np.arange(1, n+1)
    chunks = [[] for i in range(size)]
    # data needs to be divided in chunks manually for scatter
    for i in range(size):
        for j in range(n//size):
            chunks[i].append(data[i*(n//size)+j])
else:
    data = None
    chunks = None

# Scatter the data array to all processes
chunks = comm.scatter(chunks, root=0)
print("Process", rank, "has received ", chunks)

# Compute the local sum of the subdata array
local_sum = np.sum(chunks)

# Reduce the local sum to obtain the global sum
global_sum = comm.reduce(local_sum, op=MPI.SUM, root=0)

# Print the result on the root process
if rank == 0:
    print("The sum of the array is", global_sum)


```

##### In C

##### Output

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output9.jpg)

#### Code Example: Global Dot

 It first initializes MPI and divides an array of integers from 1 to n into size chunks using numpy. The scatter function is then called to send the appropriate chunk of data to each process. Each process receives its own chunk of data and computes the sum of its local chunk using the numpy sum function. Finally, the local sums are combined into a global sum using the reduce function with the MPI.SUM operator, and the root process prints the result.

##### In Python

```
from mpi4py import MPI
import numpy as np

comm = MPI.COMM_WORLD
rank = comm.rank
size = comm.size
n = 2 * size

if rank == 0:
    x = np.arange(1, n+1)
    y = np.arange(1, n+1)
    chunks_x = [[] for i in range(size)]
    chunks_y = [[] for i in range(size)]
    # data needs to be divided in chunks manually for scatter
    for i in range(size):
        for j in range(n//size):
            chunks_x[i].append(x[i*(n//size)+j])
            chunks_y[i].append(y[i*(n//size)+j])
else:
    x = None
    y = None
    chunks_x = None
    chunks_y = None

# Scatter the data array to all processes
chunks_x = comm.scatter(chunks_x, root=0)
chunks_y = comm.scatter(chunks_y, root=0)
print("Process", rank, "has received ", chunks_x, "and", chunks_y)

# Compute the local sum of the subdata array
local_dot = sum([chunks_x[i] * chunks_y[i] for i in range(len(chunks_x))])

# Reduce the local sum to obtain the global sum
global_dot = comm.reduce(local_dot, op=MPI.SUM, root=0)

# Print the result on the root process
if rank == 0:
    print("The sum of the array is", global_dot)

```

##### In C

##### Output

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output10.jpg)

[Next Section]()

### References

Diaz, J., Munoz-Caro, C., & Nino, A. (2012). A survey of parallel programming models and tools in the multi and many-core era. IEEE Transactions on parallel and distributed systems, 23(8), 1369-1386

Spagnuolo, C. (2020). Coding games and programming challenges to code better. CodinGame. Retrieved April 12, 2023, from https://www.codingame.com/playgrounds/47058/have-fun-with-mpi-in-c/lets-start-to-have-fun-with-mpi 

Watson, G. (2017). Introduction. Python MPI: Introduction. Retrieved April 12, 2023, from https://nyu-cds.github.io/python-mpi/01-introduction/ 
