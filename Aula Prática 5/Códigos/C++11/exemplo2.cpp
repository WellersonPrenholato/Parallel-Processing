// Create a group of C++11 threads from the main program
//g++ -std=c++11 -pthread exemplo2.cpp
#include <iostream>
#include <thread>
#include <stdio.h>
static const int num_threads = 10;

int main() {
    std::thread t[num_threads];
    //Launch a group of threads
    for (int i = 0; i < num_threads; ++i) {
        t[i] =  std::thread([i]{
                    printf("Thread %d\n", i);
                });
    }
    //Join the threads with the main thread
    for (int i = 0; i < num_threads; ++i) {
        t[i].join();
    }
    return 0;
}
