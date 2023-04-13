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
