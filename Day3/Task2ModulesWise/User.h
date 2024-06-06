#ifndef USER_H
#define USER_H

#include<bits/stdc++.h>
#include "ATM.h"

using namespace std;

class User {
private:
    string name;

public:
    User(const string &name);
    void withdraw(int amount);
};

#endif 