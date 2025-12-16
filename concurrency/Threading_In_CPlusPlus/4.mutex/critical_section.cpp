//
// Created by light on 20-2-1.
//
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;

// int sum = 0; //shared

// mutex m;

// void *countgold() {
//     int i; //local to each thread
//     for (i = 0; i < 10000000; i++) {
//         m.lock();
//         sum += 1;
//         m.unlock();
//     }
//     return NULL;
// }

// int main() {
//     thread t1(countgold);
//     thread t2(countgold);

//     //Wait for both threads to finish
//     t1.join();
//     t2.join();

//     cout << "sum = " << sum << endl;
//     return 0;
// }

using ll =long long;

ll g_count =0;

mutex g_mutex;

const int  ITERATIONS = 1000000;

void unsafe_increment(){
    for(int i=0; i< ITERATIONS;++i){
        g_count+=1;
    }
}

void safe_increment(){
    for(int i=0;i<ITERATIONS;++i){
        lock_guard<mutex> lock(g_mutex);
        g_count+=1;
    }
}

void run_test(void (*func)(),const string& test_name){
    g_count=0;
    auto start =chrono::high_resolution_clock::now();
    thread t1(func);
    thread t2(func);

    t1.join();
    t2.join();

    auto end =chrono::high_resolution_clock::now();
    auto duration =chrono::duration_cast<chrono::microseconds>(end-start).count();
    cout << "--- " << test_name << " 测试 ---" << endl;
    cout << "  预期结果: " << (ITERATIONS * 2) << endl;
    cout << "  实际结果: " << g_count << endl;
    cout << "  耗时:     " << duration << " 毫秒" << endl;

    if (g_count != (ITERATIONS * 2)) {
        cout << "  !!! 结论: 失败 (发生了数据竞争导致结果错误) !!!" << endl;
    } else {
        cout << "  +++ 结论: 成功 (互斥锁保证了数据一致性) +++" << endl;
    }
    cout << "---------------------------------" << endl;

}

int main(){
    run_test(unsafe_increment,"unsafe");

    run_test(safe_increment,"safe");
}