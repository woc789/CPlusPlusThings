//
// Created by light on 20-1-31.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <stddef.h>
#include <functional>
#include <algorithm>


using namespace std::chrono;
using namespace std;


/**
 * 1.普通函数指针
 * 2.Lambda函数
 * 3.Functors
 * 4.非静态成员函数
 * 5.静态成员函数
 */

using ull = unsigned long long;
// ull OddSum = 0;
// ull EvenSum = 0;

struct alignas(64) PaddedSum {
    ull sum = 0;
};

// 使用填充后的结构体作为全局变量
PaddedSum OddSum_padded;
PaddedSum EvenSum_padded;

std::vector<std::thread> threads(2);

void findEven(ull start, ull end) {
    for (ull i = start; i <= end; ++i)
        if ((i & 1) == 0)
            EvenSum_padded.sum += i;
}

void findOdd(ull start, ull end) {
    for (ull i = start; i <= end; ++i)
        if ((i & 1) == 1)
            OddSum_padded.sum += i;
}

int main() {

    ull start = 0, end = 1900000000;


    auto startTime = high_resolution_clock::now();
    // std::thread t1(findEven,start,end);
    // std::thread t2(findOdd,start,end);
    threads[0]=std::thread(findEven,start,end);
    threads[1]=std::thread(findOdd,start,end);

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);

    cout << "OddSum : " << OddSum_padded.sum << endl;
    cout << "EvenSum: " << EvenSum_padded.sum << endl;
    cout << "Sec: " << duration.count() / 1000000 << endl;
    return 0;
}
