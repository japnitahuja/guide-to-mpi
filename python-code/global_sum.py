from mpi4py import MPI
import numpy as np

n = 10

comm = MPI.COMM_WORLD
rank = comm.rank
size = comm.size

if rank == 0:
    data = np.arange(1, n+1)
    chunks = [[] for i in range(size)]
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
