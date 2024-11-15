#include <iostream>

static int globalVar = 100;  // 全局变量

void functionA() {
    std::cout << "In functionA: " << globalVar << std::endl;  // 访问全局变量
}

void functionB() {
    std::cout << "In functionB: " << globalVar << std::endl;  // 访问全局变量
}

void counterFunction() {
    static int count = 0;  // 静态局部变量
    count++;
    std::cout << "The count is: " << count << std::endl;
}

/*int main() {
    //functionA();
    //functionB();
    counterFunction();  // 第一次调用，输出 1
    counterFunction();  // 第二次调用，输出 2
    counterFunction();  // 第三次调用，输出 3
    return 0;
}*/
