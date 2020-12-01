#include <mpi.h>
#include <stdio.h>
int main (int argc, char** argv){
    int rank, size, nlen ;
    char name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* get rank */
    MPI_Comm_size(MPI_COMM_WORLD, &size); /* get size */
    MPI_Get_processor_name(name, &nlen ) ;/* get name */
    if(rank == 0)
        printf("Hello world! I am process %d out of %d on %s\n ", rank, size, name);
    else
        printf("Alo mundo! Eu sou o processo %d de %d em %s\n ", rank, size, name);
    MPI_Finalize();
    return 0;
}