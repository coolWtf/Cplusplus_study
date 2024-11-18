//C++_study/OOP/Inhieri.cpp
#include <iostream>
using namespace std;

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
