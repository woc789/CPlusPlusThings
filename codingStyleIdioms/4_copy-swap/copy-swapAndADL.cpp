//
// Created by light on 19-12-9.
//
#include <iostream>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;


// copy and swap : https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
// ADL : https://stackoverflow.com/questions/8111677/what-is-argument-dependent-lookup-aka-adl-or-koenig-lookup

namespace A {
    template<typename T>
    class smart_ptr {
    public:
        smart_ptr() noexcept : ptr_(new T()) {

        }

        smart_ptr(const T &ptr) noexcept : ptr_(new T(ptr)) {

        }

        smart_ptr(smart_ptr &rhs) noexcept {
            std::cout << "copy ctor" << std::endl;
            ptr_ = rhs.release();       // 释放所有权,此时rhs的ptr_指针为nullptr
        }

        // 方法1：为了避免自赋值,通常采用下面写法   不好!  不具备异常安全,只具备自我赋值安全性
//        smart_ptr &operator=(const smart_ptr &rhs) {
//            if (*this != rhs) {
//                delete ptr_;
//                ptr_ = new T(rhs.ptr_);  // 当new 发生异常,此时ptr_指向的而是一块被删除区域,而不是被赋值对象的区域
//                return *this;
//            }
//            return *this;
//        }
        // 方法2：如果new出现异常,ptr_会保持原装!  也可以处理自我赋值! 还是不够好!
//        smart_ptr &operator=(const smart_ptr &rhs) {
//            T *origin = ptr_;
//            ptr_ = new T(rhs.ptr_);
//            delete origin;
//            return *this;
//        }
        // 方法3：copy and swap 很好!
//        smart_ptr &operator=(smart_ptr &rhs) noexcept {
//            smart_ptr tmp(rhs);
//            swap(tmp);
//            return *this;
//        }

        // 方法4：同方法3,改为传值
        // 既适用于copy ctor也适用于 move ctor
        smart_ptr &operator=(smart_ptr rhs) noexcept {
            swap(rhs);
            return *this;
        }
        // move ctor
        smart_ptr(smart_ptr &&rhs) noexcept {
            std::cout << "move ctor" << std::endl;
            ptr_ = rhs.ptr_;
            if (ptr_)
                rhs.ptr_ = nullptr;
        }

        ~smart_ptr(){
            delete ptr_;
        }

        // move assignment
//        smart_ptr &operator=(smart_ptr &&rhs) noexcept {
//            std::cout << "move assignment" << std::endl;
//            smart_ptr tmp(rhs);
//            swap(rhs);
//            return *this;
//        }

        void swap(smart_ptr &rhs) noexcept { // noexcept == throw() 保证不抛出异常
            using std::swap;
            swap(ptr_, rhs.ptr_);
        }

        T *release() noexcept {
            T *ptr = ptr_;
            ptr_ = nullptr;
            return ptr;
        }

        T *get() const noexcept {
            return ptr_;
        }

    private:
        T *ptr_;
    };

// 提供一个非成员swap函数for ADL(Argument Dependent Lookup)
    template<typename T>
    void swap(A::smart_ptr<T> &lhs, A::smart_ptr<T> &rhs) noexcept {
        lhs.swap(rhs);
    }
}
// 注释开启,会引发ADL冲突
//namespace std {
//    // 提供一个非成员swap函数for ADL(Argument Dependent Lookup)
//    template<typename T>
//    void swap(A::smart_ptr<T> &lhs, A::smart_ptr<T> &rhs) noexcept {
//        lhs.swap(rhs);
//    }
//
//}

class NetworkConnection{
private:
    string id_;
    int *data_;

public:
    NetworkConnection() : id_("Default"), data_(nullptr) { 
        std::cout << "--> [Connection] established: DEFAULT <--\n";
    }
    
    NetworkConnection(const string& id):id_(id),data_(new int(rand()%1000+5000)){
        cout<<"--> [Connection] established :"<< id_ << "(Data Ptr:" <<data_ << ")<--\n";
    }

    NetworkConnection(const NetworkConnection& other):id_(other.id_+"_COPY"),data_(new int(*other.data_)){
    cout<< "--> [Connection] Deep Copied" << id_ <<"<--\n";        
    }

    ~NetworkConnection(){
        if(data_){
            cout<< "<-- [Connection] closed:" <<id_ <<"Data:" <<*data_ <<")-->\n";
            delete data_;
            data_ =nullptr;
        }
    }

    string get_info() const{
        return "ID:"+id_+",Data Value:"+to_string(*data_);
    }

};


A::smart_ptr<NetworkConnection> create_resource_rvalue(const string& name){
    cout<< "\n--- Function: Creating temporary resource ---\n";
    return A::smart_ptr<NetworkConnection>(NetworkConnection(name));
}


int main(){
    using A::smart_ptr;
    cout<<"======================A.初始化阶段=================\n";
    smart_ptr<NetworkConnection> s1(NetworkConnection("Primary-A"));
    smart_ptr<NetworkConnection> s2;

    cout<<"======================B.显示移动构造=================\n";
    smart_ptr<NetworkConnection> s3=move(s1);

    cout<<"s3 Info:"<<(s3.get()?s3.get()->get_info():"NULL")<<"\n";
    cout<<"s1 Status (after move):" <<(s1.get()?"Has Resource":"NULL") <<"\n";
    
    cout << "\n============== C. 函数返回后的移动赋值 ==============\n";
    
    s2= create_resource_rvalue("Temporary-B");

    cout << "s2 Info: " << (s2.get() ? s2.get()->get_info() : "NULL") << "\n";

    cout << "\n============== D. 非 const 左值拷贝构造 (特殊行为!) ==============\n";

    smart_ptr<NetworkConnection> s4=s3;

    cout << "s4 Info: " << (s4.get() ? s4.get()->get_info() : "NULL") << "\n";
    cout << "s3 Status (after pseudo-copy): " << (s3.get() ? "Has Resource" : "NULL") << "\n";
    
    cout << "\n============== E. 销毁阶段 ==============\n";
    return 0;
}



// int main() {

//     using std::swap;
//     A::smart_ptr<std::string> s1("hello"), s2("world");
//     // 交换前
//     std::cout << *s1.get() << " " << *s2.get() << std::endl;
//     swap(s1, s2);      // 这里swap 能够通过Koenig搜索或者说ADL根据s1与s2的命名空间来查找swap函数
//     // 交换后
//     std::cout << *s1.get() << " " << *s2.get() << std::endl;
// //    s1 = s2;

//     A::smart_ptr<std::string> s3 = s1;
//     A::smart_ptr<std::string> s4 = std::move(s1);
// }