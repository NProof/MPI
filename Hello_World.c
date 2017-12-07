#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
 char processor_name[MPI_MAX_PROCESSOR_NAME];
 int len;

 MPI_Init(&argc, &argv);

 MPI_Get_processor_name(processor_name, &len);
 printf("Hello World from %s\n", processor_name);

 MPI_Finalize();
 
 return 0;
}
