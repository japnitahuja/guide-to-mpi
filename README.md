# Guide to MPI in Python and C

## Table of Contents

1. [Overview](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/Overview.md)
2. [Communicator](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/Communicator.md)
3. Point to Point Communication
   - [Sending and Receiving Messages](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/Messages.md)
   - [Blocking and Non-blocking]()
4. Collectives
   - [Broadcast and Reduce]()
   - [Gather and Scatter]()

## Installation for Python

### On Windows:

On each computer node run:

```
pip install mpi4py
```

Download MSMPI from https://www.microsoft.com/en-us/download/details.aspx?id=100593

Add to Environment variables

## Installation for C

### Windows Subsystem/Linux

To start MPI Programming you need to install MPI resources on your system. Those resources will run all MPI functions. So, if you miss this step you will not able to compile or run a single program. This is the main step of MPI programming. Run the below command to install MPI on your system.

```
sudo apt install openmpi-bin libopenmpi-dev
```

This step may ask upto 5 minutes to complete and requires almost 100 MB space on your disk. Press ‘Y’ as response.

After this step you can run a C program file.

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
