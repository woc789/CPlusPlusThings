/* 1.1_类之间嵌套.cpp */
//
// Created by light on 19-12-9.
//

// #include <iostream>

// class Animal {
// public:
//     Animal() {     //默认构造函数
//         std::cout << "Animal() is called" << std::endl;
//     }

//     Animal(const Animal &) {
//         std::cout << "Animal (const Animal &) is called" << std::endl;
//     }

//     Animal &operator=(const Animal &) {
//         std::cout << "Animal & operator=(const Animal &) is called" << std::endl;
//         return *this;
//     }

//     ~Animal() {
//         std::cout << "~Animal() is called" << std::endl;
//     }
// };

// class Dog {
// public:
//     // 第一种： 使用初始化列表。
//     Dog(const Animal &animal) : __animal(animal) {
//         std::cout << "Dog(const Animal &animal) is called" << std::endl;
//     }
//     // 第二种：构造函数赋值来初始化对象。
// //    Dog(const Animal &animal) {
// //        __animal = animal;
// //        std::cout << "Dog(const Animal &animal) is called" << std::endl;
// //    }
//     ~Dog() {
//         std::cout << "~Dog() is called" << std::endl;
//     }

// private:
//     Animal __animal;

// };

// int main() {
//     Animal animal;
//     std::cout << std::endl;
//     Dog d(animal);
//     std::cout << std::endl;

//     return 0;
// }

#include <iostream>
#include <string>

using std::string;

class Mouth {
public:
    Mouth(){
        std::cout <<"生成一张嘴" << std::endl;
    }
    void mouth_eat(){
        std::cout<<"咀嚼食物\n"<<std::endl;
    }
};

class Dog {
private:
        string name;
        Mouth mouth;
public:
    // 第一种： 使用初始化列表。
    Dog(string n) :name(n) {
        std::cout << "这是我的狗,名字叫做" << n << std::endl;
    }

    void eat(){
        mouth.mouth_eat();
    }

    ~Dog() {
        std::cout << "~Dog() is called" << std::endl;
    }

    
};

int main() {
    Dog Mydog("wdx");
    Mydog.eat();

    return 0;
}