// //
// // Created by light on 19-11-5.
// //
// #include <iostream>
// #include <thread>
// #include <unistd.h>
// #include <vector>
// #include <algorithm>
// #include <functional>

// using namespace std;

// void some_function() {}

// void some_other_function() {}

// // std::thread不支持拷贝语义。
// // std::thread支持移动语义。



// // scoped_thread实例
// void do_something(int i) {
//     cout << i << endl;
// }

// struct func {
//     int &i;

//     func(int &i_) : i(i_) {}

//     void operator()() {
//         for (unsigned j = 0; j < 1000000; ++j) {
//             do_something(i);
//         }
//     }
// };

// class scoped_thread {
//     std::thread t;
// public:
//     explicit scoped_thread(std::thread t_) :                 // 1
//             t(std::move(t_)) {
//         if (!t.joinable())                                     // 2
//             throw std::logic_error("No thread");
//     }

//     ~scoped_thread() {
//         t.join();                                            // 3
//     }

//     scoped_thread(scoped_thread const &) = delete;

//     scoped_thread &operator=(scoped_thread const &) = delete;
// };

// void do_work(unsigned id) {}

// void f() {
//     std::vector<std::thread> threads;
//     for (unsigned i = 0; i < 20; ++i) {
//         threads.push_back(std::thread(do_work, i)); // 产生线程
//     }
//     std::for_each(threads.begin(), threads.end(),
//                   std::mem_fn(&std::thread::join)); // 对每个线程调用join()
// }

// int main() {
// //    std::thread t1(some_function); // 构造一个thread对象t1
// //    std::thread t2 = std::move(t1); // 把t1 move给另外一个thread对象t2，t1不再管理之前的线程了。
// //    // 这句不需要std::move()，从临时变量进行移动是自动和隐式的。调用的是operator=(std::thread&&)
// //    t1 = std::thread(some_other_function);
// //    std::thread t3;
// //    t3 = std::move(t2); // 把t2 move给t3
// //    // 把t3 move给t1，非法。因为`t1`已经有了一个相关的线程，会调用`std::terminate()`来终止程序。
// //    t1 = std::move(t3);
//     f();
//     return 0;
// }、


#include <iostream>
#include <thread>
#include <memory>
#include <chrono>
#include <stdexcept>
#include <utility> // 包含 std::move

using namespace std;

class scoped_thread {
    std::thread t;
public:
    explicit scoped_thread(std::thread t_):t(move(t_)){
        if(!t.joinable())
        throw std::logic_error("No thread");
    }

    ~scoped_thread(){
        t.join();
        cout<<"[Scoped] 析构函数执行：线程已安全 join。"<<endl;
    }
    scoped_thread(scoped_thread const &) = delete;
    scoped_thread &operator=(scoped_thread const &) = delete;
};

void backgroud_worker(int duration_s){
    cout << "[Worker] 任务开始，休眠 " << duration_s << " 秒..." << endl;
    this_thread::sleep_for(chrono::seconds(duration_s));
    cout << "[Worker] 任务完成。" << endl;
}

void perform_task_and_exit(){
    cout << "--- 函数 perform_task_and_exit() 开始 ---" << endl;
    std::thread temp_t(backgroud_worker,5);

    scoped_thread st(std::move(temp_t));

    cout << "[Main] 主线程继续执行，st 正在看守 worker。" << endl;

    cout << "--- 函数 perform_task_and_exit() 即将退出 ---" << endl;
}

int main(){
    try{
        perform_task_and_exit();
    } catch(const exception&e){
        cerr << "[Main] 捕获到异常: " << e.what() << endl;
    }

    cout << "--- 程序安全结束 ---" << endl;
    return 0;
}