#include <thread>
#include <vector>
#include <iostream>
#include <unistd.h>

#define CANT_THREADS 10

using namespace std;

void f() {
    this_thread::sleep_for(500ms);
    // puts("Hola! Soy un thread"); es igual al cout
    cout << "Hola! Soy un thread" << endl;
}

// Para ejecutar: g++ ej1-a.cpp -o ej1-a -std=c++2a -pthread

int main() {
    vector<thread> threads;
    
    for(int i = 0; i < CANT_THREADS; i++) {
        threads.emplace_back(f);
        threads[i].join();
    }

    return 0;
}