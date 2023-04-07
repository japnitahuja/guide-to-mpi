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
