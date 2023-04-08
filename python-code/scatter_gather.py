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
