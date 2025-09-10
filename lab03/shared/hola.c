/*
 ============================================================================
  MPI Hello World - Docker Compose Cluster
  ----------------------------------------
  This program demonstrates a simple MPI "Hello World" example that runs
  across multiple containers (master + clients).

  Steps to run (good practices):

  1. Start the MPI cluster (containers in background):
       $ sudo docker compose up -d

  2. Enter the master container:
       $ sudo docker exec -it master bash

  3. Switch to the mpiuser account:
       # su - mpiuser

  4. Navigate to the shared project directory:
       $ cd ~/PCyP

  5. Compile the program:
       $ mpicc hola.c -o hola.out

  6. Run the program across all hosts:
       $ mpirun -host master,client1,client2 ./hola.out

  7. Stop the cluster when done:
       $ sudo docker compose down
 ============================================================================
*/

#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <limits.h>
int main(int argc, char **argv)
{
  int rank, size;
  char hostname[HOST_NAME_MAX];
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  gethostname(hostname, HOST_NAME_MAX);
  printf("Hola desde el proceso %d de %d en el host %s\n",
         rank, size, hostname);
  MPI_Finalize();
  return 0;
}