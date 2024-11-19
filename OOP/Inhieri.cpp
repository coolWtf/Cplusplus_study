//C++_study/OOP/Inhieri.cpp
#include <iostream>
using namespace std;

class A {
public:
    int value;
    void show(){
        cout << "AAAAAA." << endl;
    }
};

class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {};


class Animal {
public:
    void eat() {
        cout << "This animal eats food." << endl;
    }
    virtual void makeSound() {
        cout << "This animal makes a sound." << endl;
    }
};
 
 //继承的类方法重名时
class buru_Animal {
public:
    void eat() {
        cout << "This buru_Animal eats food." << endl; 
    }
    virtual void makeSound() {
        cout << "This buru_Animal makes a sound." << endl;
    }
};

class Dog : public Animal, protected buru_Animal {
public:
    //重写父类方法
    void eat (){
        cout << "This buru_Animal eats food." << endl;
    }
    //明确使用规则
    /*void eat(){
        Animal::eat();
    }*/
    void makeSound() override { // 重写父类方法
        cout << "The dog barks." << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() override { // 重写父类方法
        cout << "The cat meows." << endl;
    }
};

int main() {
    D d;
    C c;
    B b;
    d.value = 30;
    cout<<d.value<<endl;
    c.value = 20;
    cout<<d.value<<endl;
    cout<<c.value<<endl;
    cout<<b.value<<endl;
    cout<<d.C::value<<endl;  //40
    cout<<d.B::value<<endl;  //40
    d.B::value = 60;
    cout<<d.value<<endl;     //60
    cout<<d.C::value<<endl;  //60
    cout<<d.B::value<<endl;  //60
    cout<<c.value<<endl;     //20
    d.show();
    b.show();
    Animal animal;
    Dog dog;
    Cat cat;

    animal.eat();
    dog.eat();
    cat.eat();

    animal.makeSound();
    dog.makeSound();
    cat.makeSound();
    return 0;
}
