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
