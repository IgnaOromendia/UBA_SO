#include <thread>
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <cassert>
#include <atomic>

#define N 100
#define THREAD_COUNT 5

using namespace std;

atomic<int> pos(0);
vector<int> pos_per_thread(THREAD_COUNT);

void verify(vector<int> v1, vector<int> v2, vector<int> v3) {
    cout << "v1 = [" << v1[0] << ", " << v1[1] << ", " << ", ..., " << v1[N - 2] << ", " << v1[N - 1] << "]" << endl;
    cout << "v2 = [" << v2[0] << ", " << v2[1] << ", " << ", ..., " << v2[N - 2] << ", " << v2[N - 1] << "]" << endl;
    cout << "v3 = [" << v3[0] << ", " << v3[1] << ", " << ", ..., " << v3[N - 2] << ", " << v3[N - 1] << "]" << endl;

    for (int i = 0; i < N; ++i) {
        assert(v3[i] == v1[i] * v2[i]);
    }

    cout << "[";
    for(int i = 0; i < THREAD_COUNT - 1; i++) {
        cout << pos_per_thread[i] << ", ";
    }
    cout << pos_per_thread[THREAD_COUNT - 1] << "]" << endl;

}

void calculate(vector<int>& v1, vector<int>& v2, vector<int>& v3, int t_i) {
    int i;
    while((i = pos++) < N) {
        v3[i] = v1[i] * v2[i];
        pos_per_thread[t_i]++;
        this_thread::sleep_for(100ms * (t_i + 1));
    }
}


int main() {
    vector<thread> threads;
    vector<int> v1(N);
    vector<int> v2(N);
    iota(v1.begin(), v1.end(), 1);
    iota(v2.begin(), v2.end(), N + 1);

    vector<int> v3(N);
    
    for(int i = 0; i < THREAD_COUNT; i++) {
        threads.emplace_back(calculate, ref(v1), ref(v2), ref(v3), i);
    }

    for(auto &t : threads) {
        t.join();
    }    

    verify(v1, v2, v3);
    return 0;
}