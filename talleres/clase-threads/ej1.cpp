#include <thread>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <mutex>

#define CANT_THREADS 10
#define CANT_SALUDOS 5

using namespace std;

mutex mtx;

void f(int* i) {
    /* Inciso a,b,c
    this_thread::sleep_for(1000ms * (*i));
    // puts("Hola! Soy un thread"); es igual al cout
    cout << s << ": " << (*i) << endl; */

    // Inciso d - solucion 1
    for(int j = 0; j < CANT_SALUDOS; j++) {
        mtx.lock();
        cout << "Hola! Soy el thread: " << (*i) << endl;
        // mtx.unlock();

        this_thread::sleep_for(100ms);

        // mtx.lock();
        cout << "Chau! Saludos desde: " << (*i) << endl;
        mtx.unlock();

        this_thread::sleep_for(200ms);
    }

    // Inciso d - solucion 2
    for(int j = 0; j < CANT_SALUDOS; j++) {
        lock_guard<mutex> lock(mtx);
        cout << "Hola! Soy el thread: " << (*i) << endl;
        this_thread::sleep_for(100ms);
        cout << "Chau! Saludos desde: " << (*i) << endl;
        //this_thread::sleep_for(200ms);
    }
}

// Para ejecutar: g++ ej1.cpp -o ej1 -std=c++2a -pthread

int main() {
    vector<thread> threads;
    vector<int> numeros;

    numeros.resize(CANT_THREADS);

    for(int i = 0; i < CANT_THREADS; i++) {
        numeros[i] = i;
        threads.emplace_back(f, &numeros[i]);
        // Si pongo el join aca, el programa se ejecuta secuencialmente
    }

    for(auto &t : threads) {
        t.join();
    }

    return 0;
}