# guide-to-mpi

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

## Install MPI on Your System
To start MPI Programming you need to install MPI resources on your system. Those resources will run all MPI functions. So, if you miss this step you will not able to compile or run a single program. This is the main step of MPI programming. Run the below command to install MPI on your system.

'''$ sudo apt install openmpi-bin libopenmpi-dev'''
This step may ask upto 5 minutes to complete and requires almost 100 MB space on your disk. Press ‘Y’ as response.

After this step you can run a C program file.
