//C++_study/OOP/Polymorphism/Com-time.cpp
#include <iostream>
void print(int x) {
    std::cout << "Integer: " << x << std::endl;
}
void print(double x) {
    std::cout << "Double: " << x << std::endl;
}
class Complex {
public:
    double real, imag;
    Complex(double r, double i) : real(r), imag(i) {}
    Complex operator+(const Complex &c) {
        return Complex(real + c.real, imag + c.imag);
    }
};
int main() {
    print(10);    // 调用 print(int)
    print(3.14);  // 调用 print(double)
    Complex c1(1.0, 2.0), c2(2.5, 3.5);
    Complex c3 = c1 + c2;  // 调用重载的 +
    std::cout << "Real: " << c3.real << ", Imag: " << c3.imag << std::endl;  //Real:3.5,Imag: 5.5
    return 0;
}
