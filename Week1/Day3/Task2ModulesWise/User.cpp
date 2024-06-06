#include "User.h"
#include<bits/stdc++.h>
using namespace std;

User::User(const string &name) : name(name) {}

void User::withdraw(int amount) {
    try {
        cout << name << " is withdrawing " << amount << " INR:" << endl;
        Withdraw result = ATM::getInstance().withdraw(amount);
        result.display();
    } catch (const exception &e) {
        cout << e.what() << endl;
    }
}