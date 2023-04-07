## hello_world.c
This code is a simple example of an MPI program in C that prints a "Hello world" message from each process in the MPI communicator.

After initializing the MPI environment using MPI_Init(), the program gets the rank of the current process and the total number of processes using MPI_Comm_rank() and MPI_Comm_size(), respectively. It then prints a message to the console using printf() that includes the process rank and total number of processes.

Finally, the program finalizes the MPI environment using MPI_Finalize() and returns 0.

When this program is run on multiple processes using an MPI launcher like mpirun or mpiexec, each process will print its own message to the console. The order in which the messages are printed is not guaranteed, as the processes can execute in any order.

##Global_sum.c

This program first creates an array of 100 integers and scatters it to all processes. Each process then computes the local sum of its portion of the array and sends it to the root process using the MPI_Reduce() function. The root process then sums up all the local sums to obtain the global sum, and prints it to the console.

To run this program on your laptop, you can follow the same steps as in the previous example. Make sure to compile the program using the MPI compiler and run it using the MPI launcher, specifying the number of processes you want to use with the -n option.

##Global_dot.c

This program first creates two arrays of 100 integers and scatters them to all processes. Each process then computes the local dot product of its portion of the arrays and sends it to the root process using the MPI_Reduce() function. The root process then sums up all the local dot products to obtain the global dot product, and prints it to the console.

To run this program on your laptop, you can follow the same steps as in the previous examples. Make sure to compile the program using the MPI compiler and run it using the MPI launcher, specifying the number of processes you want to use with the -n option.
