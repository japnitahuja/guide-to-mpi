# Guide to MPI in Python and C

This guide is designed to provide you with a comprehensive understanding of the Message Passing Interface (MPI) and how to use it in your parallel programming projects. MPI is a widely used parallel programming framework that allows multiple processors to communicate and coordinate with each other. It is commonly used in scientific computing, numerical simulations, and other high-performance computing applications. We will be covering both mpi4py for Python and OpenMPI for C.

## Table of Contents

1. [Overview](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/Overview.md)
2. [Communicator](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/Communicator.md)
3. Point to Point Communication: One to One Communication
   - [Sending and Receiving Messages](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/Messages.md)
   - [Blocking and Non-blocking](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/BlockingandNonblocking.md)
4. Collectives: One to Many or Many to Many Communication
   - [Broadcast](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/Broadcast.md)
   - [Gather and Scatter](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/ScatterandGather.md)
   - [Scatter and Reduce](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/ScatterandReduce.md)
5. Hybrid Systems

## Installation for Python

### On Windows:

On each computer node run:

```
pip install mpi4py
```

To run MPI programs on your system you also need to download MSMPI from https://www.microsoft.com/en-us/download/details.aspx?id=100593

Do not forget to add MSMPI to Environment variables once it's installed.

## Installation for C

### Windows Subsystem/Linux

To start MPI Programming you need to install MPI resources. Run the command below to install MPI on your system.

```
sudo apt install openmpi-bin libopenmpi-dev
```

## Usage in Python

```
mpiexec -n numprocesses python -m mpi4py pyfile
```

Example:

```
mpiexec -n 2 python -m mpi4py hello_world.py
```

## Usage in C

To compile a MPI program written in C run the command:

```
mpicc file_name.c -o file_name
```

After compiling a file you need to run it to see the output. Compiling a program means the program is converted into machine language. To see the output you have to run the following command:

```
mpiexec -n numprocesses ./file_name
```

In some programs you might have to use mpirun instead of mpiexec.

Example:

```
mpicc hello_world.c -o hello_world
```

```
mpiexec -n 2 ./hello_world
```

## Conclusion

This repository provides a starting point for learning about message passing interface. The examples provided here can be used as a reference for implementing MPI in python and C. If you have any questions or suggestions, feel free to open an issue or submit a pull request.

## License

[MIT](https://choosealicense.com/licenses/mit/)
