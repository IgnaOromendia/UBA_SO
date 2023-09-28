#include <thread>
#include <iostream>
#include <semaphore.h>

#define MSG_COUNT 5

using namespace std;

sem_t permiso_1;
sem_t permiso_2;

void subrutina(string s, chrono::milliseconds t) {
    for(int i = 0; i < MSG_COUNT; i++) {
        cout << i <<": EJECUTANDO " << s << endl;
        this_thread::sleep_for(t);
    }
}

void f1() {
    subrutina("F1 (A)", 100ms);
    sem_post(&permiso_1);
    sem_wait(&permiso_2);
    subrutina("F1 (B)", 200ms);
}

void f2() {
    subrutina("F2 (A)", 500ms);
    sem_post(&permiso_2);
    sem_wait(&permiso_1);
    subrutina("F2 (B)", 10ms);
}

int main() {
    sem_init(&permiso_1, 0, 0);
    sem_init(&permiso_2, 0, 0);

    thread t1(f1);
    thread t2(f2);

    t1.join();
    t2.join();

    sem_destroy(&permiso_1);
    sem_destroy(&permiso_2);

    return 0;
}