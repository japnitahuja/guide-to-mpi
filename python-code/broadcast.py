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
