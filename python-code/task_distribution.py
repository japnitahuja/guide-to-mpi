from mpi4py import MPI

comm = MPI.COMM_WORLD  # accessing the communicator object
rank = comm.rank  # getting the rank of the current process

if(rank == 0):
    print("Doing the task of process 0.")
elif(rank == 1):
    print("Doing the task of process 1.")
elif(rank == 2):
    print("Doing the task of process 2.")
else:
    print("Doing the leftover task.")
