## Sending and Receiving Messages

Processes communicate with each other by sending and receiving messages. This is also known as point to point communication as one node explicity communicates with another node. The following steps are undertaken to send and receive messages:

1. Process 1 gets the data ready for the message
2. Process 1 sends a message to another process (destination) using the Send function
3. Process 2 decides that it wants to receive a message from process one (source)
4. Process 2 receives the message by calling the Recv function

Thus the sent message is only received if it is indicated by the destination process.

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/messages.png)

#### Code Example: Sending and Receiving Data

##### In Python

###### Comm.Send(obj, dest=0, tag=0)
- Comm: Communicator
- obj: Data we wish to send
- dest (int): Destination Process Rank
- tag (int): Message tag

###### Comm.Recv(obj, source=0, tag=0)
- Comm: Communicator
- obj: Data we wish to receive
- source (int): Source Process Rank
- tag (int): Message tag

```
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
```

##### In C

###### MPI_Send(void* data,int count,MPI_Datatype datatype,int destination,int tag,MPI_Comm communicator)
- data: Data to be sent
- count: Number of data items
- datatype: Datatype of data
- destination: Destination Process Rank
- tag: Message tag
- communicator: Communicator object

###### MPI_Recv(void* data,int count,MPI_Datatype datatype,int source,int tag,MPI_Comm communicator,MPI_Status* status)
- data: Data to be received
- count: Number of data items
- datatype: Datatype of data
- source: Source Process Rank
- obj: Data we wish to receive
- tag: Message tag
- status: information about the message received

```
#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int shared = rank + 100;

    if (rank == 0)
    {
        int data = shared;
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("From process %d we sent %d\n", rank, data);
    }
    else if (rank == 1)
    {
        int data;
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("On process %d we received %d\n", rank, data);
    }

    MPI_Finalize();
    return 0;
}
```

##### Output

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/output3.jpg)

### References

Spagnuolo, C. (2020). Coding games and programming challenges to code better. CodinGame. Retrieved April 12, 2023, from https://www.codingame.com/playgrounds/47058/have-fun-with-mpi-in-c/lets-start-to-have-fun-with-mpi

Watson, G. (2017). Introduction. Python MPI: Introduction. Retrieved April 12, 2023, from https://nyu-cds.github.io/python-mpi/01-introduction/ 
