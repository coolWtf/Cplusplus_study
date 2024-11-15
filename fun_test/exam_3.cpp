#include <iostream>

class MyClass {
public:
    static int staticVar;  // 静态成员变量
    int nonStatic;  //非静态成员变量
    static void staticFunction() {  // 静态成员函数
        int a = 10;
        std::cout << a << std::endl;
        //std::cout << nonStatic << std::endl;   //访问非静态成员变量，报错。
        std::cout << "Static member function called." << std::endl;
        std::cout << "Static variable value: " << staticVar << std::endl;
    }
};

// 静态成员变量必须在类外定义
//int MyClass::staticVar = 10;  // 静态成员变量初始化

int main() {
    // 通过类名直接调用静态成员函数
    MyClass::staticFunction();  // 输出：Static member function called. Static variable value: 10

    // 通过类的对象来调用静态成员函数
    MyClass obj;
    obj.staticFunction();  // 也可以通过对象调用，但推荐通过类名调用

    return 0;
}
