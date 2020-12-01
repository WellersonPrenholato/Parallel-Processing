#include<mpi.h>
#include<stdio.h>
int main(int argc, char** argv){
    printf("Antes...\n");
    MPI_Init(&argc, &argv);
    printf("Hello world!\n");
    MPI_Finalize () ;
    printf("Depois...\n") ;
    return 0;
}