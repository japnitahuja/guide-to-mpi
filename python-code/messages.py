from mpi4py import MPI

comm = MPI.COMM_WORLD  # accessing the communicator object
rank = comm.rank  # getting the rank of the current process

if(rank == 0):
    data = rank+100
    comm.send(data, dest=1)  # sending data to process with rank of dest
    print("From process", rank, "we sent", data)
elif(rank == 1):
    # receiving data from process with rank of source
    data = comm.recv(source=0)
    print("On process", rank, "we received", data)
