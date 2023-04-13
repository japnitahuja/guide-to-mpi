## Scatter and Gather

### Scatter

Scatter sends data from one processes to all processes much like broadcast however, it divides the data into smaller pieces and equally distributes it.

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/scatter.jpg)

#### Code Example: Scattering

##### In Python

###### Comm.Scatter(sendobj, root=0)
- sendobj: data to be scattered
- root: process that will scatter

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

# Scatter the data array to all processes
data = comm.scatter(data, root=0)
print("Process", rank, "has received ", data)
```

##### In C

##### Output

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output7.png)

### Gather

Gather does the opposite of scatter. It gets data from each process, combines it into an array and sends it to the root process.

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/gather.jpg)

#### Code Example: Scattering and Gathering

This program scatters an array, performs a computation on the number it received (here it is adding 10) and then sends it back to be gathered.

##### In Python

###### Comm.Gather(sendobj, root=0)
- sendobj: data to be gathered
- root: process that will gather

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

# Scatter the data array to all processes
data = comm.scatter(data, root=0)
print("Process", rank, "has received ", data)
data += 10

data = comm.gather(data, root=0)

# Print the result on the root process
if rank == 0:
    print("The gathered result is", data)

```

##### In C

##### Output

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output8.png)


[Next Section]()

### References

Diaz, J., Munoz-Caro, C., & Nino, A. (2012). A survey of parallel programming models and tools in the multi and many-core era. IEEE Transactions on parallel and distributed systems, 23(8), 1369-1386

Spagnuolo, C. (2020). Coding games and programming challenges to code better. CodinGame. Retrieved April 12, 2023, from https://www.codingame.com/playgrounds/47058/have-fun-with-mpi-in-c/lets-start-to-have-fun-with-mpi 

Watson, G. (2017). Introduction. Python MPI: Introduction. Retrieved April 12, 2023, from https://nyu-cds.github.io/python-mpi/01-introduction/ 
