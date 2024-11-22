#include <iostream>
using namespace std;
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
    // 没有重写 func
    ~Derived(){
        cout<<"delete Derived"<<endl;
    }
};

class Base_xu{
public:
    virtual void func1() = 0;
};

class Derived1 : public Base_xu {
    // 没有重写 func1
};
int main() {
    Base* obj = new Derived();
    obj->func(); // 调用 Base 的 func
    delete obj;
    return 0;
}
