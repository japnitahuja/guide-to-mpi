## Hybrid Systems

Shared model system and distributed systems can be combined to leverage the strengths of both. Shared model systems come with significant advantages in performance and simplicity since all processes can access the memory. However, what they lack in scalability can be taken from the distributed computing model. Each computer node can have a shared model parallel system working on it like OpenMP or pthreads whereas for the communication between these nodes, MPI can be used. 

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/hybrid.png)

### Pthreads

A thread is a lightweight process. This is a low level method implemented using a library which provides way to create threads, destroy threads, mutually exclude threads using locks and condition variables. It follows the fork/join programming paradigm. 

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/forkjoin.png)

OpenMP is a directive based approach where directives define the work sharing scheme of the processor.
