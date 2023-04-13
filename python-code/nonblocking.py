from mpi4py import MPI
import numpy
import time

comm = MPI.COMM_WORLD
rank = comm.rank

randNum = numpy.zeros(1)

# send a message from rank 0 to rank 1 using non-blocking communication
if rank == 0:
    randNum = numpy.random.random_sample(1)
    req = comm.Isend(randNum, dest=1)
    print("Rank {} sent data: {}".format(rank, randNum))
elif rank == 1:
    req = comm.Irecv(randNum,source=0)
    
# do some other computation while waiting for communication to complete
print("Rank {} is doing some other computation...".format(rank))
result = 0
for i in range(10000000):
    result += i

# wait for the communication to complete
req.Wait()

# print the received message
if rank == 1:
    print("Rank {} received data: {}".format(rank, randNum))