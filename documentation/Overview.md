## Overview

### What is MPI?

MPI or message passing interface is the agreed upon standard to support parallel programming in distributed system. Processes communicate via messages which can refer to raw data, signals or acknowledgements. MPI is not a new language or a library, it is a specification of how the communication should occur. OpenMPI and mpi4py are libraries built according to the MPI standard.

### Why MPI?

In a shared memory system, each processor is connected to a shared memory which can be used for communication. However, for distributed computing where each processor has its own memory making messages the only natural way to communicate.

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/sharedvsdistributed.png)

#### Pros
- Portability: Can run on both shared and distributed memory systems unlike other parallel programming frameworks like OpenMP, OpenCL or pthreads
- Scalability: As the scale of the problem increases, distributed memory systems are preferred over shared memory systems. Increasing processors in distributed systems may be more viable.
- Flexibility: MPI provides high level of control over the communication and synchronization of processes.

#### Cons
- Overheads: Performance is limited by communication speeds between the nodes.
- Complexity: Can be harder to debug as distribution of data and messages needs to be explicitly programmed.


### How does MPI work?

MPI launches a user specified number of processes at the start of the program. Usually, this is the number of cores in a system. The processes have their own memory and do not share it with other processes. Each process has a unique `Rank` associated with it. This value is used to differentiate between the processes in the code. We will see an example of this in the next section.

[Next Section](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/Communicator.md)

### References

Diaz, J., Munoz-Caro, C., & Nino, A. (2012). A survey of parallel programming models and tools in the multi and many-core era. IEEE Transactions on parallel and distributed systems, 23(8), 1369-1386

Spagnuolo, C. (2020). Coding games and programming challenges to code better. CodinGame. Retrieved April 12, 2023, from https://www.codingame.com/playgrounds/47058/have-fun-with-mpi-in-c/lets-start-to-have-fun-with-mpi 
