//C++_study/OOP/class_study.cpp
#include "iostream"
using namespace std;
class Person {
public:
    string name;
    int age;

    Person() {  // 默认构造函数
        name = "Unknown";
        age = 0;
    }

    Person(string n, int a) : name(n), age(a) {}  // 参数化构造函数

    Person(const Person& other) {  // 拷贝构造函数
        name = other.name;
        age = other.age;
    }
    //移动构造函数，核心为将源对象的资源转移到目标对象，确保源对象的资源被释放。
    //noexcept 是指不会抛出异常
    Person(Person&& other) noexcept {
        name = move(other.name);
        age = other.age;
        other.age = 0;
    }

};

// 管理动态分配的资源时 必须手动写析构函数
class String {
private:
    char* data; // 动态分配的内存
public:
    // 构造函数
    String(const char* str) {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }

    // 必须手动编写析构函数来释放内存
    ~String() {
        delete[] data; // 释放动态分配的内存
        std::cout << "Destructor called, memory released.\n";
    }

    void print() const {
        std::cout << data << std::endl;
    }
};

//拥有对外部资源的特殊责任
class FileHandler {
private:
    std::ofstream file;
public:
    FileHandler(const char* filename) {
        file.open(filename, std::ios::out);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file.");
        }
    }

    ~FileHandler() {
        if (file.is_open()) {
            file.close(); // 释放文件资源
            std::cout << "File closed.\n";
        }
    }

    void write(const std::string& text) {
        file << text << std::endl;
    }
};

class Base {
public:
    virtual void func() {
        std::cout << "Base::func called\n";
    }
    //作为基类并且有派生类继承 就需要显式写基类虚析构函数，否则派生类delete时会发生内存泄漏
    virtual ~Base(){
        cout<<"delete Base"<<endl;
    }   

};
class Derived : public Base {
    ~Derived(){
        cout<<"delete Derived"<<endl;
    }
};

int main() {
    Person p;  // 自动调用默认构造函数
    cout << p.name << " is " << p.age << " years old." << endl;
    Person p1("Alice", 25); //调用参数化构造函数
    cout << p1.name << " is " << p1.age << " years old." << endl;
    Person p2 = p1;  // 调用拷贝构造函数   等价于  Person p2(p1);
    cout << p2.name << " is " << p2.age << " years old." << endl;
    Person p3 = move(p2);   //调用移动构造函数   这里move是一个标准库函数，只是将p2转化为右值引用
    cout << p2.name << " is " << p2.age << " years old." << endl;
    cout << p3.name << " is " << p3.age << " years old." << endl;
    Person p4 = 
    return 0;
}
