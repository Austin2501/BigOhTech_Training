#include<bits/stdc++.h>
#include "ATM.h"
#include "User.h"
using namespace std;

int main() {
    ATM &atm = ATM::getInstance();

    atm.addMoney(2000, 20);
    atm.addMoney(500, 2);
    atm.addMoney(200, 5);
    atm.addMoney(100, 10);

    cout << "Initial ATM Balance:" << endl;
    atm.displayBalance();
    cout << endl;

    User Vineet("Vineet");
    Vineet.withdraw(5300);

    cout << "Remaining ATM Balance:" << endl;
    atm.displayBalance();
    cout << endl;

    atm.Demonitization(2000);

    cout << "ATM Balance after demonetizing 2000 INR notes:" << endl;
    atm.displayBalance();
    cout << endl;

    atm.addMoney(5000, 10);

    cout << "ATM Balance after adding 5000 INR notes:" << endl;
    atm.displayBalance();
    cout << endl;

    Vineet.withdraw(5000);
    cout << endl;

    cout << "Remaining ATM Balance:" << endl;
    atm.displayBalance();
    cout << endl;

    return 0;
}