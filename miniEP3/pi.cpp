
// Compilar código Sequencial: icpc pi.cpp -o piSeq
// Para submeter o job: qsub -l nodes=1:gpu:ppn=2 -d . miniEP3seq.sh

// Compilar código Paralelo: mpiicpc pi.cpp -o pi
// Para submeter o job: 
// - Usando 1 nó:  qsub -l nodes=1:gpu:ppn=2 -d . miniEP3par.sh
// - Usando 2 nós: qsub -l nodes=2:gpu:ppn=2 -d . miniEP3par.sh

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <iomanip>
#include <sys/time.h>
#include <mpi.h>

using namespace std;

double MyClock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

long double f(long double a){
 return (4.0 / (1.0 + a*a));
}

int main(int argc, char *argv[]){
    
    int ret, rank, size, tag;
    long long num_steps;
    
    long double step;
    long long i;
    long double x, pi, pi_aux, sum;
    
    MPI_Init(&argc, &argv);
    
    double inicio = MyClock();
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    cin >> num_steps;
    MPI_Bcast(&num_steps, 1, MPI_LONG, 0, MPI_COMM_WORLD);
        
    step = (long double) 1/num_steps;
    
    sum = 0.0;

    for (i=rank; i< num_steps; i+=size) {
        x = (i + 0.5)*step;
        sum += f(x);
    }
        
    pi_aux = step * sum;
        
    MPI_Reduce(&pi_aux, &pi, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if(rank == 0){
        cout << fixed << setprecision(25);
        cout << "      #Intervalos: " << num_steps << endl;
        cout << " Valor encontrado: " << pi << endl;
        cout << "   Valor esperado: " << M_PI << endl;
        cout << "    Erro Relativo: " << fabs(pi - M_PI)/M_PI << endl;

        //3.141592653589793238462643383279502884197

        double tempoTotal = (MyClock()-inicio)/CLOCKS_PER_SEC;
        cout << fixed << setprecision(5);
        cout << "Tempo gasto (seg): " << tempoTotal << endl << endl;
    }
    
    MPI_Finalize();
    return 0;
}
