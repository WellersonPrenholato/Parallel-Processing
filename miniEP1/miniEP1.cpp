///Para comipilar:
//g++ -o miniEp -O3 -std=c++11 miniEp1.cpp -pthread -lm
//icpc -o miniEp -O3 -std=c++11 miniEp1.cpp -pthread -lm

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <thread>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Imprime uma mensagem de erro e encerra o programa com o código da falha
#define DIE(...) { \
        fprintf(stderr, __VA_ARGS__); \
        exit(EXIT_FAILURE); \
}

typedef long long ll;

unsigned numThreads;
ll numElementos;
ll totalPrimos=0;

double MyClock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

bool check_prime(ll n) 
{ 
    if (n <= 1) 
        return false; 
    if (n <= 3) 
        return true;

    if (n == 3 || n == 5 || n == 7) 
        return true; 
  
    if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0 ) 
        return false; 
  
    for (int i = 5; i * i <= n; i = i + 6) 
        if (n % i == 0 || n % (i + 2) == 0) 
            return false; 
  
    return true;
}

ll formula (ll x){
    
    ll resultado = 2*(x*x) - 1;

    return resultado;
}

void mythread(int t) {

    ll ini = t*numElementos/numThreads == 0 ? 1: (t * (numElementos/numThreads))+1;
    ll fim = t+1 == numThreads ? numElementos: (t*(numElementos/numThreads)) + (numElementos/numThreads);

//     printf("Thread %d: vetor[%lld ... %lld]\n", t, ini, fim);
    int contagem =0;
    for (ll i = ini; i <= fim; ++i) {

      if (check_prime(formula(i))){
          contagem++;
      }
    }
    
//     printf("Thread %d: terminou\n", t);

//     printf("N primos de [%lld ... %lld]: %d\n", ini, fim, contagem);
    totalPrimos += contagem;
}

void preencheVetor(){

    vector<thread> threads(numThreads);

    //Preenche o valor
    for(int i=0; i<numThreads; i++){
        threads[i] = thread(mythread, i);
    }

    for (int i=0; i<numThreads; i++) {
        threads[i].join();
    }
}

int main(int argc, char *argv[]) {
    double inicio = MyClock();
//     srand(time(0));

    // Valida os argumentos
    if (argc != 3 || sscanf(argv[1], "%u", &numThreads) != 1 || sscanf(argv[2], "%lld", &numElementos) != 1) {
        printf("usage: %s <numThreads> <numElementos>\n", argv[0]);
        return 1;
    }

    if (numElementos < 0)
        DIE("Tamanho do vetor invalido\n");

    // Você deve paraleliazar apenas essa função
    preencheVetor();

//     printf("Total de PRIMOS: %lld\n", totalPrimos);

    printf("%.5lf\n", (MyClock()-inicio)/CLOCKS_PER_SEC); //segundos
    
    return 0;
}