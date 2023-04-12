## Overview

### What is MPI?

MPI or message passing interface is the agreed upon standard to support parallel programming in distributed system. Processes communicate via messages which can refer to raw data, signals or acknowledgements.

### Why MPI?

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/sharedvsdistributed.jpg)

### How does MPI work?

MPI launches a user specified number of processes at the start of the program. Usually, this is the number of cores in a system. The processes have their own memory and do not share it with other processes.

Each process has a unique `Rank` associated with it. This value is used to differentiate between the processes in the code.
