//g++ -std=c++11 thread.cpp

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <thread>
#include <vector>
#include <sys/time.h>
#include <time.h>

using namespace std;

#define MAX  50000000
#define FUNCAO(I) ceil((sqrt(I)*sqrt(I)+pow(I, 100)-log(I)+log(I)))
//round((sqrt(I)*sqrt(I)+pow(I, 100)-log(I)+log(I)))

int NUM_THREADS;
double vetor[MAX];

double MyClock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}


void mythread(int arg) {
    int t = arg;
    int i; 
    int ini = t*MAX/NUM_THREADS;
    int fim = t*MAX/NUM_THREADS + MAX/NUM_THREADS;
    printf("Thread %d: vetor[%d ... %d]\n", t, ini, fim-1);
    for (i = ini; i < fim; i++) {
      vetor[i] = FUNCAO(i);
    }
    printf("Thread %d: terminou\n", t);
}

                                                                             
int main(int argc, char *argv[]) {
    double inicio = MyClock();
    if (argc != 2) {
      fprintf(stderr, "usage: ./a.out <threads>\n");
      exit(1);
    }

    NUM_THREADS = atoi(argv[1]);
   
    //thread *threads = (thread *)malloc(NUM_THREADS*sizeof(thread*));
    vector<thread> threads(NUM_THREADS);

    int i;
    for (i = 0; i < NUM_THREADS; i++) {
        threads[i] = thread(mythread, i);
    }
    
    for (i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }

    printf("Tempo gasto: %.5lf\n", (MyClock()-inicio)/CLOCKS_PER_SEC);
    
    return 0;
}
