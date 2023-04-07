# Guide to MPI in Python and C

## Table of Contents

1. [Overview](https://github.com/japnitahuja/guide-to-mpi/blob/main/documentation/Overview.md)

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

`$ sudo apt install openmpi-bin libopenmpi-dev`

This step may ask upto 5 minutes to complete and requires almost 100 MB space on your disk. Press ‘Y’ as response.

After this step you can run a C program file.

## Usage in Python

`mpiexec -n numprocs python -m mpi4py pyfile`

Example:
`mpiexec -n 2 python -m mpi4py hello_world.py`

## Usage in C

## Conclusion

This repository provides a starting point for learning about message passing interface. The examples provided here can be used as a reference for implementing MPI in python and C. If you have any questions or suggestions, feel free to open an issue or submit a pull request.

## License

[MIT](https://choosealicense.com/licenses/mit/)
