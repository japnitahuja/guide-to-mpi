## What are Distributed and Shared memory systems?
The two main types of parallel systems, or architectures, are shared memory and distributed memory. We have a single memory address space that is available to all processors in shared memory architectures. Shared memory devices have long been a feature of servers and expensive workstations. However, because multi-core processors share the main memory among all of their cores, common desktop computers currently fall into this group. On the other side, there is no global address space in distributed memory systems. Every processor has a separate memory. It is common to see this architectural concept in networked or distributed systems, such as computer clusters or grids. It is possible to create hybrid shared distributed memory systems, of course. In shared memory architectures, a pure shared memory model typically uses the OpenMP API, while on distributed memory systems, a pure message passing model typically uses the MPI API. Today's most powerful and quick computers use both shared and distributed memory architectures. This gives programmers freedom when adjusting parallelism for optimal efficiency and a good balance between the computational and communication demands. In addition, the Heterogeneous Parallel Programming (HPP) model was made possible by the fact that General Purpose Computation on GPUs (GPGPUs) are now available in real multi-core systems. HPP aims to take advantage of multi-core CPUs and multi-core GPUs.
Several parallel programming paradigms can be combined in what is referred to as hybrid parallel programming, in accordance with all these hybrid architectures. Intelligently implementing hybrid parallel programmes can significantly speed up implementations of MPI or OpenMP that would otherwise be pure. The same is true for hybrid programming that uses distributed architectures and GPUs .

## Hybrid programming models
The intention is to maximise the benefits of shared and distributed models: the efficiency, memory savings and ease of programming of the shared memory model with the scalability of the distributed memory one. Therefore, we may rely on combining the currently available programming models and tools rather than creating new runtimes or languages. The method used here is called hybrid (parallel) programming. With the modern hybrid hardware designs that are currently in use, this programming approach is a software trend.
The fundamental concept is to leverage shared memory (often OpenMP or even Pthreads) within a node and message forwarding (typically MPI) between the dispersed nodes. GPUs can be used as a source of processing power in hybrid programming.
Although OpenCL or other GPU programming methods could be utilised in this situation, CUDA is typically used.
OpenCL's application is not particularly extended in the field of hybrid programming, despite the fact that it directly supports multi-GPU and GPU+CPU programming.

## Pure Parallel Programming model
Here, we consider parallel programming models using a pure shared or distributed memory approach.

### POSIX THREAD:
The Pthreads, or Portable Operating System Interface
(POSIX) Threads, is a set of C programming language types
and procedure calls [7], [22], [23]. Pthreads is implemented
as a header (pthread.h) and a library for creating and
manipulating each thread. The Pthreads library provides
functions for creating and destroying threads and for
coordinating thread activities via constructs designed to
ensure exclusive access to selected memory locations (locks
and condition variables).

### Shared Memory OpenMP:
OpenMP is a shared memory application programming interface (API) whose aim is to ease shared memory
parallel programming. The OpenMP multithreading interface  is specifically designed to support High Performance Computing community. It
is also portable across shared memory architectures.

### Message Passing
A parallel programming approach called message passing uses message exchange to facilitate communication between processes. But over time, a standard for this approach has emerged and taken hold: the Message Passing Interface (MPI). A specification for message-passing operations is called MPI. MPI is not a language; it is a library. It details the names, calling patterns, and outcomes of the subroutines or functions that Fortran, C, or C++ programmes should call. The programmes can therefore be created using standard compilers, but they also need to be linked with the MPI library.
The message-passing model is addressed by MPI. The simultaneous processes in this approach each have their own memory address space. When a portion of one process's address space is copied into the address space of another process, communication takes place.
Only when the first process executes a send operation and the second process executes a receive operation does this cooperative operation take place. Similar to Pthreads, workload partitioning and task mapping in MPI must be done by the programmer. The tasks that are to be computed by each process must be managed by programmers. Point-to-point, collective, one-sided, and parallel I/O operations are all part of MPI's communication paradigms.
