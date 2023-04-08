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
data = comm.bcast(data, root=0)
print("Process", rank, "has received ", data)

# Reduce the local sum to obtain the global sum
global_sum = comm.reduce(data, op=MPI.SUM, root=0)

# Print the result on the root process
if rank == 0:
    print("The sum of the array is", global_sum)
