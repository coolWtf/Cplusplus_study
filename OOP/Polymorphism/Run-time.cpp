//C++_study/OOP/Polymorphism/Run-time.cpp
#include <iostream>
#include <vector>
using namespace std;
class Animal {
public:
    virtual void sound() {
        std::cout << "Animal makes a sound." << std::endl;
    }
};

class Dog : public Animal {
public:
    void sound() override {
        std::cout << "Dog barks." << std::endl;
    }
};

class Cat : public Animal {
public:
    void sound() override {
        std::cout << "Cat meows." << std::endl;
    }
};
void Fun_sound(Animal & animal){
    animal.sound();
}
int main() {
    Animal *a1 = new Dog();
    Animal *a2 = new Cat();
    Dog a3;

    a1->sound();  // 指针的方式 调用 Dog 的 sound
    a2->sound();  // 指针的方式 调用 Cat 的 sound

    Fun_sound(*a1);// 对象引用的方式 调用 Dog 的 sound
    Fun_sound(*a2);// 对象引用的方式 调用 Cat 的 sound

    (*a1).sound(); //
    a3.sound(); //这种是静态绑定，在编译阶段就确定了调用的是谁的方法
    //使用动态绑定可以可以根据实际类型调用方法，动态绑定让 zoo 容器可以同时管理 Dog 和 Cat 的实例，而不需要写两套代码。
    //新增其他动物类型（例如 Bird），只需继承 Animal 并实现 sound 方法即可，无需修改主程序。
    vector<Animal*> zoo;
    zoo.push_back(new Dog());
    zoo.push_back(new Cat());
    for (auto animal : zoo) {
        animal->sound(); // 动态绑定，根据实际类型调用方法
    }

    for (auto animal : zoo) {
        delete animal; // 释放内存
    }
    delete a1;  //释放内存 调用 Dog 和 Animal 的析构函数
    delete a2;

    return 0;
}
