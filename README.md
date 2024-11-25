@[TOC](C++学习笔记，持续更新)

# 写在开头
相关代码更新到GitHub仓库，[仓库地址](https://github.com/coolWtf/Cplusplus_study.git)
https://github.com/coolWtf/Cplusplus_study.git
通过秋招这两个月，认清了自己的目标，不再盲目的追求国企，专注于技术的深耕，从现在开始把之前项目中用到的技术点，以及基础知识重新梳理一遍， 从语法，数据结构，面向对象，标准库，高级特性这几个方向一步一步扎实基础。  
11.13更新  这两天还是有一些企业面试，优先更新面试高频问题，后续再一步步更新基础。
## 基础语法与数据类型
### 1.一个C++文件是如何运行的
编译过程有四个阶段：**预处理**，**编译**，**汇编**和**链接**。接下来拿一个简单程序做演示。

```cpp
#include <iostream>
#define N 100
void greet() {
    std::cout << "Hello, world!" << std::endl;
}

int main() {
    greet();
    std::cout << N << std::endl;
    return 0;
}

```
#### 预处理
使用g++ -E命令进行预处理得到.i文件。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/87c7b31312a742cd9bb582773630a190.png)

可以看到预处理器负责处理源代码中的指令，比如 #include、#define 等。
- 将 #include <iostream> 替换为 iostream 标头文件的内容。前两万八千多行就是标头文件内容
- 处理条件编译指令，如 #ifdef、#ifndef 等。
- 替换宏定义和其他预处理指令。 可以看出直接将N替换成了100
#### 编译
预处理完成后，编译器会将预处理的代码转化为汇编代码。汇编代码是与具体硬件架构相关的低级语言，接近机器指令。
`g++ -S exam_0.i -o exam.s`得到编译后的文件。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/a5fb49b7aabc4f66a6ae12e2f0f768a1.png)

在此期间会进行三个任务
- 将高层次的C++代码转化为汇编语言
- 进行语法和语义检查，比如变量类型检查，函数定义匹配等。
- 进行代码优化，例如常量折叠，循环展开等。

#### 汇编
在这一步，汇编程序（assembler）将汇编代码转化为机器代码，即二进制代码，这些代码能够直接被硬件执行。

```bash
g++ -C exam.s -o exam_0.o
```
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/babec1967a604517a89e5bccc3ad0c49.png
在这期间会进行两个任务。
- 将汇编代码翻译成机器语言指令。
- 分配内存地址给符号（如变量、函数等）。

**汇编的输出**： 汇编器生成一个目标文件，通常是 .o 或 .obj 文件，比如 example.o。这个文件是二进制格式，但尚未完全具备可执行性，因为它可能引用了其他目标文件中定义的符号（比如库函数）。

#### 链接
链接器会将多个目标文件以及库文件链接成一个最终的可执行文件。这一步会解析和合并不同模块之间的符号。
链接期间进行的任务：
- 处理函数调用的外部依赖，找到 std::cout 等符号的定义。
- 将各目标文件中的符号合并，去除多余的符号。
- 设置入口点（如 main 函数）和其他必要的元数据。

**链接的输出**：链接器生成最终的可执行文件（比如在 Linux 下为 exam.out，在 Windows 下可能是 exam.exe），这个文件包含了所有已解析的符号和链接后的代码段，能够直接在操作系统中运行。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/590a09366fa545beb08d66f2254c2b3d.png)
上述简单的展示了C++文件运行的过程。


### 2.基本语法：标识符，注释，代码块，头文件
#### 标识符
经常会在各种笔试题中遇到，判断哪些标识符是不正确的。
在C++中，标识符是用来命名变量、函数、类、对象、枚举、命名空间等的符号。标识符的命名遵循特定规则：
**命名规则**：
- 只能使用字母（a-z，A-Z）、数字（0-9）和下划线（_）。
- 不能以数字开头，例如 1variable 是非法的。
- 严格区分大小写，MyVariable 和 myvariable 是两个不同的标识符。
- 不能与 C++ 关键字相同（例如 int、class、return 等）。

示例

```cpp
int age;              // 合法的标识符
float _height;        // 合法的标识符
std::string name123;  // 合法的标识符

int 2day;             // 非法标识符，不能以数字开头
int float;            // 非法标识符，不能使用关键字

```
#### 注释
只有两种方式-单行（//）和多行（/*   xxxxx  */）

#### 代码块
代码块是指用大括号 {} 包围的一段代码，它通常用于函数、循环、条件语句等。代码块会将一组语句放在一起，表示它们是一个整体。

#### 头文件
头文件用于声明库函数、类、全局变量等的接口，便于代码的复用和组织。C++ 通过 #include 指令来包含头文件中的内容。

## 函数
函数是非常重要的一个模块，必须深刻把握理解。接下来介绍函数的基本内容。
### 函数的定义与声明
#### 函数的定义
包括返回类型、函数名、参数列表以及函数体。其基本结构如下：

```cpp
return_type function_name(parameter_list) {
    // 函数体
    // 执行某些操作
    return value;  // 如果返回类型不是 void，则必须有返回值
}

```
#### C++函数返回多个值
在python中可以有多个返回值，但是在C++中只能有一个返回值，要想达到返回多个值的目的，可以自定义一个类，然后返回类型为这个类，可以得到多个成员变量从而达到多个返回值的目的。也有一些C++定好的类如pair<bool,int>,tuple<bool,int,int>来达到这个目的。
#### 函数的声明
函数的声明只是告诉编译器函数的返回类型、名称及其参数类型，但不包含函数体。声明用于提前通知编译器函数的存在，通常在头文件中声明。声明是必须的，特别是当函数定义位于 main() 函数之后，或者在多个文件中时。

```cpp
return_type function_name(parameter_list);  // 函数原型（声明）
```

声明时并未给函数分配内存，只有定义时候才会分配。
#### 参数
- 形参：函数定义时使用的参数变量，指定数据类型和名称。
- 实参： 调用函数时实际传递给函数的值。
### 作用域和生命周期（面试高频）
作用域和生命周期定义了变量的可见性和存在时间。
#### 局部变量
- 定义：局部变量是在函数内部声明的变量，只能在该函数或代码块内部访问。
- 作用域： 仅在函数内部。
- 生命周期：局部变量在函数调用时创建，函数执行完毕后销毁。

```cpp
void function() {
    int localVar = 5;  // 局部变量
    std::cout << localVar << std::endl;
}  // localVar 在函数结束时销毁

```
#### 全局变量
- 定义：全局变量是在所有函数外部声明的变量，通常位于文件的顶部。
- 作用域：全局变量的作用域是整个程序（在定义它之后的所有代码段）。
- 访问方式：全局变量在程序的任何地方都可以直接访问，无论是在函数内部，还是在不同的源文件中，只要是同一个文件或者通过 extern 声明在其他文件中。
- 生命周期：全局变量在程序运行期间一直存在，从程序开始到程序结束。

file1.cpp  
在这个文件中定义了全局变量globalVar 并且可以看到在文件内部任意函数都可以访问到
```cpp
//file1.cpp
#include <iostream>
int globalVar = 100;  // 全局变量
void functionA() {
    std::cout << "In functionA: " << globalVar << std::endl;  // 访问全局变量
}
void functionB() {
    std::cout << "In functionB: " << globalVar << std::endl;  // 访问全局变量
}
int main() {
    functionA();
    functionB();
    return 0;
}
```
file2.cpp 
在这个文件中使用extern 关键字引入globalVar ，使其可以在其他文件中被访问。

```cpp
// file2.cpp
#include <iostream>
// 使用 extern 声明全局变量
extern int globalVar;  // 声明在 file1.cpp 中定义的 globalVar
void modifyGlobalVar() {
    globalVar = 200;  // 修改全局变量
    std::cout << "globalVar in file2.cpp after modification: " << globalVar << std::endl;
}
```
main.cpp
在这个文件中来调用file1及file2的函数

```cpp
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
```
注意，对这三个文件进行链接时，只能有一个文件包含main（）函数，否则程序会找不到正确的入口导致报错。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/502bb91f59134201833a9508ad143f49.png)
将file1.cpp main函数注释掉后重新编译运行。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/937768ec183d4865b9b6e9b82c2e3908.png)
#### static关键字（面试高频）
##### 静态局部变量
- 定义：是一种在函数调用之间保持其值的局部变量。
- 作用域： 仅在函数内部可见。
- 生命周期： 局部变量在函数执行结束后会被销毁，但使用 static 修饰的局部变量在函数执行结束后不会被销毁，而是会保留其值，直到下一次函数调用时继续使用。生命周期持续整个程序运行。

```cpp
#include <iostream>

void counterFunction() {
    static int count = 0;  // 静态局部变量
    count++;
    std::cout << "The count is: " << count << std::endl;
}
int main() {
    counterFunction();  // 第一次调用，输出 1
    counterFunction();  // 第二次调用，输出 2
    counterFunction();  // 第三次调用，输出 3
    return 0;
}

```
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/dddc6e1b019143a29f10791a1840e139.png)
可以看出，仅初始化一次。
##### 静态全局变量
- 定义： 是指在文件内部作用域有效的全局变量。
- 作用域： 使用 static 修饰的全局变量不能被其他文件访问，因此它的作用域仅限于定义它的源文件。
- 生命周期： 生命周期持续整个程序运行。

```cpp
//file1.cpp
//将上述全局变量的示例代码globalVar 加static修饰
static int globalVar = 100;  // 全局变量
//重新将文件链接就会报错 因为加了static关键词后仅对文件内部可见，即使外部文件加了extern关键词也不能访问
```
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/ebcd98cf7c714a4d9a8a1fb4cf2c00f7.png)
##### 静态全局函数
static修饰普通全局函数（即在类外）
与静态全局变量类似，静态函数的作用域被限制在定义它的文件中，这有助于避免名称冲突。
##### 静态成员函数及静态成员变量（类中）

**静态成员函数**
是**属于类本身**而不是某个特定的类对象的。
因此，静态成员函数可以在没有创建对象实例的情况下被调用（直接通过类名），
并且它**无法访问非静态成员变量或非静态成员函数**，因为它不与任何对象实例关联。由于属于这个类，它**可以在文件外被调用**，作用域就不会被局限于本文件。

```cpp
//exam_3.cpp
#include <iostream>
class MyClass {
public:
    static int staticVar;  // 静态成员变量
    int nonStatic;  //非静态成员变量
    static void staticFunction() {  // 静态成员函数
        int a = 10;
        std::cout << a << std::endl;
        std::cout << nonStatic << std::endl;   //访问非静态成员变量，报错。
        std::cout << "Static member function called." << std::endl;
        std::cout << "Static variable value: " << staticVar << std::endl;
    }
};

// 静态成员变量必须在类外定义
int MyClass::staticVar = 10;  // 静态成员变量初始化

int main() {
    // 通过类名直接调用静态成员函数
    MyClass::staticFunction();  // 输出：Static member function called. Static variable value: 10

    // 通过类的对象来调用静态成员函数
    MyClass obj;
    obj.staticFunction();  // 也可以通过对象调用，但推荐通过类名调用

    return 0;
}

```
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/6bf7c8d8f4f445a8af357710e186bfcd.png)
如上述例子所示，第一次编译时没有在静态成员函数中访问非静态成员变量，可以正常运行，后续加上访问非静态成员的语句，报错。

**静态成员变量** 
是属于类本身而不是类的对象的变量。它们的生命周期是与程序的运行周期相同的，而不是每次创建类的对象时才分配内存。
**类共享**：静态成员变量被类的所有对象共享，所有对象访问的都是同一个静态成员变量。不同对象的静态成员变量值是相同的，修改一个对象的静态成员变量，所有其他对象看到的值也会改变。
**存储位置**：静态成员变量不存储在每个类实例的内存空间中，而是分配在 静态内存区域，与类的实例化对象无关。
**初始化**：静态成员变量必须在类外部进行初始化。即使它们在类内部有默认值，仍然需要在外部定义它们的初值。
**访问方式**：静态成员变量可以通过类名直接访问，而不需要创建类的对象。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/94f8b81a01b34a00ad5f11f5241df9f3.png)
静态成员变量必须在类外初始化，否则会编译出错。 将exam_3.cpp中的初始化代码注释掉会报这个错误。


## 指针和引用
### 指针
指针是一个变量，也就意味着初始化可以为空，保存着另一个变量的内存地址。
#### 指针的定义
指针的定义格式为：`type *pointerName` `type`表示指针指向的数据类型，`*` 表示指针符号。
```cpp
int x = 10;
int *p = &x;  // 定义一个指向 int 类型的指针 p，指向 x 的地址
```
#### 指针运算
- 解引用`*`:获取指针指向处地址的值。
- 地址运算符`&`:获取变量的地址
- 指针的算数运算：可以对指针执行加、减运算，例如 `p + 1` 会指向下一个内存单元（取决于类型大小）。

```cpp
int a = 10;
int *p = &a;
std::cout << *p << std::endl;  // 解引用得到 a 的值，输出 10

p = p + 1;  // p 向后移动一个 int 的大小

```
这里指针运算单级的还好，多级指针运算就比较麻烦，会在下面举出数组指针的运算，数组指针即为二级指针。

#### 空指针
空指针（nullptr）是一个不指向任何有效内存地址的指针。通过给指针赋值 nullptr 表示它不指向任何对象，通常用来检测指针是否被初始化。

```cpp
int *ptr = nullptr;
if (ptr == nullptr) {
    std::cout << "ptr 是空指针" << std::endl;
}
```
这里就是有指针和引用的区别了，指针可以为空，但是引用不行，引用是对一个已存在变量的引用
#### 指针的类型转换
C++ 中允许对指针进行类型转换，通常用于不同数据类型间的指针兼容性。

- `reinterpret_cast`：将一个指针类型转换为另一个不相关类型的指针。
- `static_cast`：用于基本类型或父子类之间的指针转换。

```cpp
#include <iostream>

struct DeviceRegister {
    // 假设设备寄存器结构体定义
    int control;
    int data;
};

int main() {
    int* memoryAddress = (int*)0x1000;  // 假设这是一块特定内存地址
    DeviceRegister* deviceRegPtr = reinterpret_cast<DeviceRegister*>(memoryAddress);
    // 现在可以通过 deviceRegPtr 去访问这块内存区域，就好像它是设备寄存器结构体所在内存一样
    std::cout << "Control register value: " << deviceRegPtr->control << std::endl;
    return 0;
}
```


```cpp
void *vptr;
int a = 42;
vptr = &a;  // 将 int 的地址赋给 void* 指针

int *intptr = static_cast<int*>(vptr);  // 使用 static_cast 转换回 int*
std::cout << *intptr << std::endl;

```
这里插一句，关于类型转化，C++有四种类型转换，static_cast、dynamic_cast、const_cast 和 reinterpret_cast。之后单独开一下节详细描述。

### 引用
引用时一个变量的别名，在定义时必须初始化，即对一个已存在的变量进行引用，且初始化后不能更改指向的对象。
#### 1.引用的定义

```cpp
int x = 10;
int &ref = x;  // 定义一个引用 ref，ref 和 x 指向同一个内存地址
ref = 20;      // 修改 ref 的值，即 x 的值也被修改为 20
```
#### 2.引用的引用场景
- 参数传递：以引用的方式进行参数传递，避免拷贝数据增加效率。
- 返回值优化： 通过引用返回对象，同样也可以避免函数返回值的拷贝。

```cpp
void increment(int &n) {  // 引用作为参数
    n++;
}
int incre(int n){ //不通过引用进行参数传递，需要对于实参进行拷贝
	n++;
	return n;    //并且需要拷贝返回值给外部变量，引用的话避免了拷贝。
}
int n = incre(n);//不通过引用的方式就需要进行两次拷贝才能得到经过函数处理后的变量。
```
### 指针与引用区别（面试高频问题）
|区别|指针  | 引用|
|--|--|--|
| 定义后是否可更改 |可以指向不同对象  |不能更改指向 |
|是否能为nullptr|可以|初始化不能为null必须引用一个对象|
|操作符|使用*访问对象地址|直接访问引用对象|
|作为参数传递时|传递的是一个对象地址|直接操作对象，不需要解引用|
|多级操作时|可以多级取地址，每一级值不同|对引用变量进行再次引用也是同一个变量进行操作|

```cpp
int main() {
    greet();
    int x = 10;
    int *fir_ptr = &x;        //一级指针fir_ptr存放x的内存地址
    int **sec_ptr = &fir_ptr; //二级指针sc_ptr 存放fir_ptr的地址
    int &ref = x;  // 定义一个引用 ref，ref 和 x 指向同一个内存地址
    ref = 20;      // 修改 ref 的值，即 x 的值也被修改为 20
    int &b = ref;  //使用b来引用ref
    std::cout << fir_ptr << std::endl;
    std::cout << *fir_ptr << std::endl;
    std::cout << sec_ptr << std::endl;
    std::cout << *sec_ptr << std::endl;
    std::cout << b << std::endl;
    return 0;
}
```
![运行结果](https://i-blog.csdnimg.cn/direct/cb5332ebc55e48b9b243b3c6cee935b6.png)
### 指针数组和数组指针


## new和malloc操作符（面试高频）

## 面向对象（OOP）
### 三大基本特性--封装，继承，多态（必问）
#### 封装
封装是指将对象的属性（数据）和方法（行为）结合在一起，隐藏对象的内部实现细节，对外提供接口来访问和操作对象。这种设计提高了代码的**安全性**和**可维护性**。

为什么要采用封装的思想：
- 访问控制：通过访问修饰符（private、protected、public）控制类成员的可见性。
- 隐藏实现细节：用户只能通过提供的接口访问对象，而不需要了解其内部实现。
- 提高安全性：防止外部直接修改对象的内部数据，确保对象状态的一致性。
示例代码：

```cpp
//C++_study/OOP/Encapsu.cpp
#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string owner;  // 账户所有者
    double balance; // 余额

public:
    // 构造函数
    BankAccount(string ownerName, double initialBalance)
        : owner(ownerName), balance(initialBalance) {}

    // 获取余额
    double getBalance() const {
        return balance;
    }

    // 存款
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: " << amount << ", New Balance: " << balance << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    // 取款
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrew: " << amount << ", New Balance: " << balance << endl;
        } else {
            cout << "Invalid withdrawal amount!" << endl;
        }
    }
};

int main() {
    BankAccount account("Alice", 1000);
    account.deposit(200);   // 存款
    account.withdraw(500);  // 取款
    account.withdraw(1000); // 超出余额
    return 0;
}

```
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/81270a3a263e4be9bdc1de9ac26bf34a.png)
#### 继承
继承允许一个类（子类）从另一个类（父类）继承属性和方法，从而实现代码的复用和扩展。子类可以直接使用父类的成员，也可以通过重写来修改父类的行为。

- 代码复用： 子类无需重新显式编写父类已有的代码。
- ##### 多继承： 一个类可以继承多个基类。
当继承的多个基类中存在重名函数时会报错，要么重写函数，要么需要明确调用规则。示例如下：
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/bf5340b0bef24595a22a6df3b5fc4e63.png)
- 访问控制：可以访问public和protected 成员变量及函数。
- 继承类型： 当一个类派生自基类，该基类可以被继承为 public、protected 或 private 几种类型。
	- 公有继承（public）：当一个类派生自公有基类时，基类的公有成员也是派生类的公有成员，基类的保护成员也是派生类的保护成员，基类的私有成员不能直接被派生类访问，但是可以通过调用基类的公有和保护成员来访问。
	- 保护继承（protected）： 当一个类派生自保护基类时，基类的公有和保护成员将成为派生类的保护成员。
	- 私有继承（private）：当一个类派生自私有基类时，基类的公有和保护成员将成为派生类的私有成员。
- 重写：子类可以重写父类的方法，提供特定的实现，如上图中makeSound方法，override只能重写基类中的虚函数，不是则将报错。如下图所示，将eat方法使用override修饰后编译出错。
 ![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/a0ad1449afcb4a169d8700bba7ea39ba.png)-
 - #####  虚继承
虚继承 是 C++ 中一种解决 多继承冲突问题 的机制，主要用于解决菱形继承结构中 重复继承同一个基类 导致的歧义和资源冗余问题。
|普通继承|虚继承  |
|--|--|
| 每条继承路径都继承一个基类示例 | 所有派生类共享基类的一个实例 |
|可能导致重估继承和歧义问题 |避免菱形继承问题 |
|内存开销较小|增加虚基类表（VBTable），少许增加开销|

```cpp
class A {
public:
    int value;
    void show(){
        cout << "AAAAAA." << endl;
    }
};

class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {};

int main() {
	D d;
    C c;
    B b;
    d.value = 30;
    cout<<d.value<<endl; //输出30
    c.value = 20;
    cout<<d.value<<endl; //输出30
    cout<<c.value<<endl; //输出20
    cout<<b.value<<endl; //由于未初始化，输出一个随机值。
    cout<<d.C::value<<endl;  //30
    cout<<d.B::value<<endl;  //30
    d.B::value = 60;
    cout<<d.value<<endl;     //60
    cout<<d.C::value<<endl;  //60
    cout<<d.B::value<<endl;  //60
    cout<<c.value<<endl;     //20
    d.show();//调用A中的方法，输出AAAA
    b.show();//同上
    //如果B,C 类中各自重写了show（）方法，那么d调用时必须指定调用哪个基类的方法。
    return 0;
}

```

-	-	当直接实例化 B 或 C 时，它们的虚基类 A 是彼此独立的，因此 value 是独立的。

	- 只有在最终派生类（如 D）中，虚基类的唯一性机制才会生效，确保 D 中的 A 实例被 B 和 C 共享。
	- 无论通过 D、B、还是 C 修改 A 的成员（如 value），都会作用于同一个 A 实例。所以，d.value、d.B::value 和 d.C::value 访问的 value 是同一个。
	- 在虚继承中，最终派生类（如 D）中虚基类的唯一实例是共享的，因此通过任何路径（D、B、C）修改虚基类的成员（如 value），都会影响其他路径访问到的值。这是虚继承用于避免菱形继承问题的核心机制。
	- 当虚继承B，C同时重写了基类的show（）方法时，必须指定调用哪一个基类的方法。



#### 多态
多态分为编译时多态，以及运行时多态。
##### 编译时多态
是指在编译期间就确定了函数或操作符的调用方式。
主要包括：

- 函数重载

```cpp
//C++_study/OOP/Polymorphism/Com-time.cpp
#include <iostream>
void print(int x) {
    std::cout << "Integer: " << x << std::endl;
}
void print(double x) {
    std::cout << "Double: " << x << std::endl;
}
int main() {
    print(10);    // 调用 print(int)
    print(3.14);  // 调用 print(double)
    return 0;
}
```

- 运算符重载

```cpp
//C++_study/OOP/Polymorphism/Com-time.cpp
#include <iostream>
class Complex {
public:
    double real, imag;
    Complex(double r, double i) : real(r), imag(i) {}
    Complex operator+(const Complex &c) {
        return Complex(real + c.real, imag + c.imag);
    }
};
int main() {
    Complex c1(1.0, 2.0), c2(2.5, 3.5);
    Complex c3 = c1 + c2;  // 调用重载的 +
    std::cout << "Real: " << c3.real << ", Imag: " << c3.imag << std::endl;  //Real:3.5,Imag: 5.5
    return 0;
}
```

- 模板
***
等之后写道模板类的时候再补充
***

其主要特点为**静态绑定**，及调用函数或操作在编译时就已经确定了。此外**执行效率高**，由于函数地址或调用方式在编译阶段就确定，运行时不需要额外开销。主要适用于操作相对固定、无需动态行为的场景。

##### 运行时多态
是指在运行期间根据对象的类型动态决定调用哪个函数。主要通过虚函数和继承实现。

实现机制：

- **虚函数表**： 每个包含虚函数的类都会有一个虚函数表，记录了类中所有虚函数的地址。每个对象通过虚指针（vptr）访问该表。
- **动态绑定**：函数调用在运行时根据对象的实际类型，通过虚指针找到对应的函数实现。
- **基类指针**：必须通过基类的指针或者引用调用虚函数。

示例代码：

```cpp
//C++_study/OOP/Polymorphism/Run-time.cpp
#include <iostream>
#include <vector>
using namespace std;
class Animal {
public:
    virtual void sound() {
        std::cout << "Animal makes a sound." << std::endl;
    }
};

class Dog : public Animal {
public:
    void sound() override {
        std::cout << "Dog barks." << std::endl;
    }
};

class Cat : public Animal {
public:
    void sound() override {
        std::cout << "Cat meows." << std::endl;
    }
};
void Fun_sound(Animal & animal){
    animal.sound();
}
int main() {
    Animal *a1 = new Dog();
    Animal *a2 = new Cat();
    Dog a3;

    a1->sound();  // 基类指针的方式 调用 Dog 的 sound
    a2->sound();  // 基类指针的方式 调用 Cat 的 sound

    Fun_sound(*a1);// 对象引用的方式 调用 Dog 的 sound
    Fun_sound(*a2);// 对象引用的方式 调用 Cat 的 sound

    (*a1).sound(); //
    a3.sound(); //这种是静态绑定，在编译阶段就确定了调用的是谁的方法
    //使用动态绑定可以可以根据实际类型调用方法，动态绑定让 zoo 容器可以同时管理 Dog 和 Cat 的实例，而不需要写两套代码。
    //新增其他动物类型（例如 Bird），只需继承 Animal 并实现 sound 方法即可，无需修改主程序。
    vector<Animal*> zoo;
    zoo.push_back(new Dog());
    zoo.push_back(new Cat());
    for (auto animal : zoo) {
        animal->sound(); // 动态绑定，根据实际类型调用方法
    }

    for (auto animal : zoo) {
        delete animal; // 释放内存
    }
    delete a1;  //释放内存 调用 Dog 和 Animal 的析构函数
    delete a2;

    return 0;
}


```

多态的核心在于动态绑定，而动态绑定依赖于基类指针或引用来实现虚函数调用。
**不使用基类指针或引用时，仅能实现静态绑定，失去了多态的动态行为**。
使用基类指针或引用，可以让代码更加通用、灵活和易于扩展，从而充分发挥面向对象编程的优势。

|特性 |编译时多态 |运行时多态|
|--|--|--|
|绑定时机|编译时绑定，静态绑定|运行时绑定，动态绑定|
|实现机制|函数重载，运算符重载，模板|继承，虚函数|
|灵活性|静态，固定的行为|动态，可扩展的行为|
|效率|高效，无其他开销|需要虚表查找，增加额外开销|
|使用场景|类型已知且无需动态行为|需要根据对象的动态类型调整行为|


***
gdb查看虚函数表
后续更新，目前还没用到gdb
***

### 类相关
类的成员变量，成员函数及其继承，多态相关问题在上面已经陈述了，这里主要讲下类的构造函数和析构函数，以及常见面试问题。
#### 构造函数（常问）
构造函数是类的一种特殊函数，在创建对象时自动调用，用于初始化对象的成员变量。
##### 四种构造函数：

- 默认构造函数：没有参数，没有显式定义构造函数时会提供默认的隐式构造函数。
- 参数构造函数：接收参数，灵活初始化对象。
- 拷贝构造函数： 使用已有对象初始化新对象，默认拷贝构造函数会按值复制成员变量。
- 移动构造函数： 用于从右值（临时对象）中转移资源。减少不必要的资源拷贝，提高性能。

```cpp
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

```
***
写到这里的时候不了解右值引用，在下面零碎小知识那一节详细描述了，可以直接去那一节看或者直接札沼右值引用这个光检测

noexcept 是 C++ 中的一个关键字，用于指定一个函数是否可能抛出异常。它在函数声明和定义时使用，声明一个函数不会抛出任何异常。
***

##### 构造函数可以为虚函数吗（常问）
不可以，
- 虚函数依赖于虚表，虚表指针在构造函数中尚未完全建立：

	- 当构造一个对象时，虚表指针（vptr） 的初始化是由基类构造函数完成的。在基类构造函数运行时，派生类的虚表还未被设置。
	- 如果允许构造函数为虚函数，在基类构造函数中调用虚函数时，无法访问派生类的虚表，也就无法实现多态行为。
- 逻辑上不符合：

	- 构造函数的职责是创建对象的实例并初始化成员变量，而虚函数的职责是允许动态绑定以实现运行时多态。这两者的目的不同，逻辑上也不适合结合。
- 构造函数本质上需要静态绑定：

	- 在构造对象时，必须明确调用哪个类的构造函数（基类或派生类）。动态绑定的虚函数与这种明确调用的要求冲突。
#### 析构函数
在对象生命周期结束时自动调用，用于释放资源。
- 语法：以 ~ 开头，没有返回值和参数。
- 作用：
	 - 清理动态分配的资源。
	 -  防止资源泄漏。

一般在类中没有手动定义析构函数时，C++ 编译器会自动生成一个**默认的析构函数**。默认析构函数是一个隐式定义的、无参数的、**非虚**的函数，它的主要作用是销毁对象并释放与对象直接关联的资源。
因此在多种情况下虚构函数必须要手动编写：
##### 哪些情况下必须手动编写虚构函数

 1. 管理动态分配的资源
当类中包含指针成员变量并在运行时使用new操作符动态地分配内存时，必须在析构函数中使用delete操作符来释放内存。这样做可防止内存泄漏。

```cpp
// 管理动态分配的资源时 必须手动写析构函数
//C++_study/OOP/class_study.cpp
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
};

```
为什么必须编写析构函数：

- 动态分配的内存不会自动释放
- 如果不手动编写析构函数，析构时不会释放 data 指向的内存，从而导致内存泄漏。

2.	 拥有对外部资源的特殊责任
当类负责管理外部资源（如文件句柄，数据库连接或者线程锁时）需要在析构函数中显式释放这些资源。

```cpp
//拥有对外部资源的特殊责任
//C++_study/OOP/class_study.cpp
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
```
为什么必须编写析构函数：

- 文件、网络连接等资源在程序运行结束时可能未被自动清理。
- 如果不显式关闭资源，会导致资源泄漏。

3.	继承的多态基类
当一个类作为基类并且可能通过基类指针或引用使用时，必须为其定义虚析构函数。如果不这样做，派生类的析构函数可能不会被正确调用，导致资源泄漏。

```cpp
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
	//这里没有显式重写基类析构函数，那么默认基类中的定义
	//delete这个对象时的调用顺序为，先调用本身的析构函数，再根据虚函数表调用基类的析构函数
    ~Derived(){
        cout<<"delete Derived"<<endl;
    }
};

int main() {
    Base* b = new Derived();
    delete b; // 通过基类指针删除对象
    return 0;
}
```

```bash
# 销毁对象时的运行结果，首先调用派生类自身的析构函数。
Base::func called
delete Derived
delete Base
```
为什么必须编写析构函数：

- 如果基类的析构函数不是虚函数，delete b 只会调用基类的析构函数，而不会调用派生类的析构函数。
- 这会导致派生类中动态分配的资源未被释放。


但基类中的析构函数去掉virtual声明时，重新运行发现只调用了基类的析构函数，并没有调用派生类的析构函数。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/453f289dab3340f987980a334e4782b3.png)


4.	实现自定义的清理行为
有些类需要在析构时执行一些特殊的操作，比如记录日志、更新状态或发送通知。

```cpp
class Logger {
private:
    std::string name;
public:
    Logger(const std::string& n) : name(n) {
        std::cout << "Logger " << name << " created.\n";
    }

    ~Logger() {
        std::cout << "Logger " << name << " destroyed.\n"; // 自定义清理行为
    }
};
```
为什么必须编写：
- 自定义的清理逻辑（如记录日志或更新全局状态）需要在析构时执行。
- 系统无法自动完成这些任务，需要通过手动编写析构函数实现。
## 零碎小知识
在写别的部分的时候，发现会涉及到其他内容，目前还不知道归类到哪一节，先写在这里
### 左值右值，右值引用
#### 左值
是指可以标识一块内存的表达式，通常是可以取地址的。左值在表达式结束后仍然存在。

- 可以取地址（使用&运算符）
- 持久存在的对象

```cpp
int x = 10;  // x 是一个左值
x = 20;      // 可以对 x 进行赋值
int* p = &x; // 可以取地址

10 = x;      // 错误！10 是一个右值，不能出现在赋值左侧
```
#### 右值
是指不与内存地址关联的表达式，通常是临时的、短暂存在的。

- 不能取地址（通常没有明确的内存地址）
- 通常是临时值

```cpp
int y = x + 5; // (x + 5) 是右值，它的结果是一个临时值
y = 42;        // 42 是右值，直接赋值给 y

```
#### 右值引用
用 && 声明的引用类型，可以绑定到右值。它的主要用途是实现**移动语义**和**完美转发**。

- 只能绑定到右值
- **避免不必要的拷贝**
- 窃取右值的资源

```cpp
int x = 10;
int&& r = 20;   // r 是一个右值引用，绑定到右值 20
r = 30;         // 修改 r 的值是合法的
std::cout << r; // 输出 30


int&& r = x; // 错误！右值引用不能绑定到左值

int&& r = std::move(x); // 合法！std::move 将 x 转换为右值

```

### 虚函数和纯虚函数
- virtual 修饰的普通虚函数
	- 允许派生类重写，但不强制
	- 如果派生类不重写，则会使用基类的定义

- 纯虚函数
	- 在基类中声明但不提供实现，派生类必须重写。
	- 如果派生类没有重写，则派生类也不能实例化，也当作一个抽象类。
	- 有个例外，基类的析构函数就算定义为纯虚函数，仍需要提供一个实现（尽管它是纯虚函数）。
```cpp
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
    // 没有重写 func1  如在实例化Derived1对象则会报错
};
int main() {
    Base* obj = new Derived();
    obj->func(); // 调用 Base 的 func
    delete obj;
    return 0;
}
```

```bash
(base) root@560fb791bdad:/202222000568/C++_study/something_other# ./xu_and_chunxu                       
Base::func called
delete Derived
delete Base
```

如上示例：虚函数，不要求强制重写，但是纯虚函数如果在派生类中不重写就不能被实例化，否则会编译错误，如下。
![在这里插入图片描述](https://i-blog.csdnimg.cn/direct/64260bc866654d10a63ed727d5254c5b.png)

