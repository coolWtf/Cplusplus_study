// main.cpp
#include <iostream>


//声明 file1.cpp中定义的函数
void functionA();
void functionB();
// 声明在 file2.cpp 中定义的函数
void modifyGlobalVar();

int main() {
    functionA();
    functionB();
    modifyGlobalVar();  // 调用修改全局变量的函数
    functionA();
    return 0;
}
