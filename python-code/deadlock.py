import numpy
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()

randNum = numpy.zeros(1)

if rank == 0:
    comm.Recv(randNum, source=1)

if rank == 1:
    comm.Recv(randNum, source=0)
