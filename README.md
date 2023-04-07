# Guide to MPP

## Installation

On Windows:

On each computer node run:

```
pip install mpi4py
```

Download MSMPI from https://www.microsoft.com/en-us/download/details.aspx?id=100593

Add to Environment variables

## Running Program

mpiexec -n numprocs python -m mpi4py pyfile

Example:
mpiexec -n 2 python -m mpi4py hello_world.py

## Install MPI on Windows Subsystem to run in C language
To start MPI Programming you need to install MPI resources on your system. Those resources will run all MPI functions. So, if you miss this step you will not able to compile or run a single program. This is the main step of MPI programming. Run the below command to install MPI on your system.

```$ sudo apt install openmpi-bin libopenmpi-dev```

This step may ask upto 5 minutes to complete and requires almost 100 MB space on your disk. Press ‘Y’ as response.

After this step you can run a C program file.
## Compile MPI Program
If you have completed the above task correctly then your environment has been set successfully. So, you can now compile any program. I will teach about writing and understanding MPI program in next step. In this step I am giving an overview to the commands only.

To compile a MPI program written in C run the command:

```$ mpicc openmpi_first.c -o first_mpi```
## Run MPI Program
After compiling a file you need to run it to see the output. Compiling a program means the program is converted into machine language. To see the output you have to run the following command:

```$ mpiexec -n 4 ./first_mpi```
