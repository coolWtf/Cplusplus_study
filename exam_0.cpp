#include <iostream>
#define N 100
void greet() {
    std::cout << "Hello, world!" << std::endl;
}

int main() {
    greet();
    int x = 10;
    int *fir_ptr = &x;        //一级指针fir_ptr存放x的内存地址
    int **sec_ptr = &fir_ptr; //二级指针sc_ptr 存放fir_ptr的地址
    int &ref = x;  // 定义一个引用 ref，ref 和 x 指向同一个内存地址
    ref = 20;      // 修改 ref 的值，即 x 的值也被修改为 20
    int &b = ref;
    std::cout << fir_ptr << std::endl;
    std::cout << *fir_ptr << std::endl;
    std::cout << sec_ptr << std::endl;
    std::cout << *sec_ptr << std::endl;
    std::cout << b << std::endl;
    return 0;
}

