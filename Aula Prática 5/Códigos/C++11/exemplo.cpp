// Create a group of C++11 threads from the main program
//g++ -std=c++11 -pthread exemplo.cpp
#include <iostream>
#include <thread>
#include <stdio.h>
static const int num_threads = 20;
//This function will be called from a thread
void call_from_thread(int tid) {
    //std::cout << "Launched by thread " << tid << std::endl;
    printf("Launched by thread %d\n", tid);
}
int main() {
    std::thread t[num_threads];
    //Launch a group of threads
    for (int i = 0; i < num_threads; ++i) {
        t[i] = std::thread(call_from_thread, i);
    }
    //Join the threads with the main thread
    for (int i = 0; i < num_threads; ++i) {
        t[i].join();
    }
    return 0;
}
