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