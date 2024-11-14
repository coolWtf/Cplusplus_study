#include <iostream>

int globalVar = 100;  // 全局变量

void functionA() {
    std::cout << "In functionA: " << globalVar << std::endl;  // 访问全局变量
}

void functionB() {
    std::cout << "In functionB: " << globalVar << std::endl;  // 访问全局变量
}

/*int main() {
    functionA();
    functionB();
    return 0;
}*/
