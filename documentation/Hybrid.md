## Hybrid Systems

Shared model system and distributed systems can be combined to leverage the strengths of both. Shared model systems come with significant advantages in performance and simplicity since all processes can access the memory. However, what they lack in scalability can be taken from the distributed computing model. Each computer node can have a shared model parallel system working on it like OpenMP or pthreads whereas for the communication between these nodes, MPI can be used. 

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/hybrid.png)

### Pthreads and MPI

A thread is a lightweight process. This is a low level method implemented using a library which provides way to create threads, destroy threads, mutually exclude threads using locks and condition variables. It follows the fork/join programming paradigm. 

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/forkjoin.png)

In the hybrid model, pthreads can be used on each computer node to divide tasks and generate results in the shared memory. And the communication between the nodes can happen via messages using MPI. Applications of this are seen in file compression and finding bounded prime numbers.

### OpenMP and MPI

OpenMP is a directive based approach where directives define the work sharing scheme of the processor. Thus, this is done at a compiler level and also follows the fork join model.

This is a popular model as both OpenMP and MPI are open sourced industry standards. OpenMP reduces the extra overheads due to messages within a node. The program is structured as MPI tasks running on each node and these MPI tasks take advantage of parallelism using OpenMP. 

Either this can happen with overlapping communication and computation or seperate communication and computation. In the first methadology, both computation and MPI communication is done by several OpenMP threads whereas in the second method computation is done by OpenMP threads but communication is left to just the master thread outside the parallel region. Usually the latter is very complicated to code. This model has been used for weather related computation before.

![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/overlappingvsnon.png)

### OpenCL and MPI

The model of OpenCL is slightly different. The device consists of work groups which contain work item (threads) that have access to one level of shared memory called local memory. Work groups have access to a different shared memory called global memory. The host communicates with device to run kernels. Only the dimension of the work group is specified by the the programmer for each task, and then work is distributed implicitly. 

 ![alt text](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/images/opencl.png)
 
The hybrid model is a very GPU focussed approach. One MPI process maps to one GPU. This model is only effective if firstly the work at hand has two levels of parallelism, at the GPU and MPI level. And secondly, there is intensive computation required for which GPUs are required.
 
 
