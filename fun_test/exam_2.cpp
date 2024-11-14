// file2.cpp
#include <iostream>

// 使用 extern 声明全局变量
extern int globalVar;  // 声明在 file1.cpp 中定义的 globalVar

void modifyGlobalVar() {
    globalVar = 200;  // 修改全局变量
    std::cout << "globalVar in file2.cpp after modification: " << globalVar << std::endl;
}
