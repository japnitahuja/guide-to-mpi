import numpy
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()

randNum = numpy.zeros(1)

if rank == 0:
    print("Process", rank, "before receiving has the number", randNum[0])
    comm.Irecv(randNum, source=1)
    print("Process", rank, "received the number", randNum[0])

if rank == 1:
    print("Process", rank, "before receiving has the number", randNum[0])
    comm.Irecv(randNum, source=0)
    print("Process", rank, "received the number", randNum[0])
