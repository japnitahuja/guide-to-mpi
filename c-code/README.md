## hello_world.c
This code is a simple example of an MPI program in C that prints a "Hello world" message from each process in the MPI communicator.

After initializing the MPI environment using MPI_Init(), the program gets the rank of the current process and the total number of processes using MPI_Comm_rank() and MPI_Comm_size(), respectively. It then prints a message to the console using printf() that includes the process rank and total number of processes.

Finally, the program finalizes the MPI environment using MPI_Finalize() and returns 0.

When this program is run on multiple processes using an MPI launcher called mpirun , each process will print its own message to the console. The order in which the messages are printed is not guaranteed, as the processes can execute in any order.

## Global_sum.c

This program first creates an array of 100 integers and scatters it to all processes. Each process then computes the local sum of its portion of the array and sends it to the root process using the MPI_Reduce() function. The root process then sums up all the local sums to obtain the global sum, and prints it to the console.

To run this program on your laptop, you can follow the same steps as in the previous example. Make sure to compile the program using the MPI compiler and run it using the MPI launcher, specifying the number of processes you want to use with the -n option.

## Global_dot.c

This program first creates two arrays of 100 integers and scatters them to all processes. Each process then computes the local dot product of its portion of the arrays and sends it to the root process using the MPI_Reduce() function. The root process then sums up all the local dot products to obtain the global dot product, and prints it to the console.

To run this program on your laptop, you can follow the same steps as in the previous examples. Make sure to compile the program using the MPI compiler and run it using the MPI launcher, specifying the number of processes you want to use with the -n option.
## messages.c
This code is a simple MPI program in C that demonstrates how to send and receive messages between two processes using MPI_Send and MPI_Recv.

After initializing the MPI environment using MPI_Init, the program gets the rank of the current process using MPI_Comm_rank. It then calculates a shared variable based on the rank of the process.

If the rank of the process is 0, it sets the value of the shared variable to a local variable called "data", and sends this value to process 1 using MPI_Send. It also prints a message to the console indicating that it has sent the value.

If the rank of the process is 1, it receives the value of the shared variable from process 0 using MPI_Recv and stores it in a local variable called "data". It then prints a message to the console indicating that it has received the value.

Finally, the program finalizes the MPI environment using MPI_Finalize and returns 0.

When this program is run on 2 processes using an MPI launcher called mpirun, it will send the value of the shared variable from process 0 to process 1, and print messages indicating that the value has been sent and received. The order in which the messages are printed may differ depending on how the processes execute.
To compile the code

```mpicc messages.c -o messages```

To run the code

```mpirun -n 2 ./messages```
## scatter_gather.c
In this example code, process 0 creates an array of integers to be scattered, and then uses MPI_Scatter to distribute the array across all processes. Each process receives a portion of the array, stored in a local receive buffer.

Each process then prints its local portion of the array to the console, so you can see how the array has been distributed.

Finally, MPI_Gather is used to collect the local arrays from all processes onto process 0. Process 0 receives each portion of the array and stores it in the original send buffer, which is then printed to the console so you can see the final result.

Note that this code assumes that the number of processes is 4, and that ARRAY_SIZE is evenly divisible by the number of processes. You can modify the code to handle different array sizes and numbers of processes as needed.
To compile the code

 ```mpicc scatter_gather.c -o scatter_gather```
 
To run the code

``` mpirun -n 4 ./scatter_gather```
 
 ## Broadcast.c
 In this code, the root process (rank 0) broadcasts an integer value to all other processes using the MPI_Bcast() function. All other processes receive the broadcasted value using the same function.
 
 To compile the code

 ``` mpicc broadcast.c -o broadcast```
 
To run the code

``` mpirun -n 4 ./broadcast ```
 ## Broadcast_reduce.c
 
 In this code, the root process broadcasts an integer value to all other processes using the MPI_Bcast() function. Then, all processes perform a reduction operation on their local data using the MPI_Reduce() function, which sums up all the values from different processes and stores the result in the root process.

 
To run this code, you can compile it with an MPI compiler (e.g. mpicc) and then run it using an MPI runtime environment (e.g. mpirun). 

To compile the code:

``` mpicc broadcast_reduce.c -o broadcast_reduce```

To run the code with 4 processes:

```mpirun -n 4 ./broadcast_reduce```

This will run the code with 4 processes, where the root process broadcasts the value 0 to all other processes. Then, all processes perform a reduction operation on their local data and send the result to the root process. Finally, the root process prints out the sum of all data received from different processes.

## nonblocking.c

It creates a group of MPI processes, and each process is assigned a rank within the group.

If the process rank is 0, it generates a random number and sends it to process 1 using non-blocking communication. If the process rank is 1, it receives the message sent by process 0 using non-blocking communication.

After sending or receiving the message, each process performs some other computations while waiting for the communication to complete. Once the communication is completed, process 1 prints the received message.

The code demonstrates how non-blocking communication can be used to overlap computation and communication to improve program performance.





