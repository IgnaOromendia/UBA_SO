#include <thread>
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <cassert>

#define N 100
#define THREAD_COUNT 5

using namespace std;

void verify(vector<int> v1, vector<int> v2, vector<int> v3) {
    cout << "v1 = [" << v1[0] << ", " << v1[1] << ", " << ", ..., " << v1[N - 2] << ", " << v1[N - 1] << "]" << endl;
    cout << "v2 = [" << v2[0] << ", " << v2[1] << ", " << ", ..., " << v2[N - 2] << ", " << v2[N - 1] << "]" << endl;
    cout << "v3 = [" << v3[0] << ", " << v3[1] << ", " << ", ..., " << v3[N - 2] << ", " << v3[N - 1] << "]" << endl;

    for (int i = 0; i < N; ++i) {
        assert(v3[i] == v1[i] * v2[i]);
    }
}

void calculate(int from, vector<int>::iterator v1_begin, vector<int>::iterator v1_end,
                         vector<int>::iterator v2_begin, vector<int>::iterator v2_end,
                         vector<int>::iterator v3_begin, vector<int>::iterator v3_end) {
    while(v1_begin != v1_end and v2_begin != v2_end and v3_begin != v3_end) {
        *v3_begin = (*v1_begin) * (*v2_begin);
        v1_begin++;
        v2_begin++;
        v3_begin++;
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
        int step = N / THREAD_COUNT;
        int from = i * step;
        int to = (i + 1) * step;
        threads.emplace_back(calculate, i * 20, v1.begin() + from, v1.begin() + to,
                                                v2.begin() + from, v2.begin() + to,
                                                v3.begin() + from, v3.begin() + to);
    }

    for(auto &t : threads) {
        t.join();
    }    

    verify(v1, v2, v3);

    return 0;
}