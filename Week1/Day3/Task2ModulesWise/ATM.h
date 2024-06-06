#ifndef ATM_H
#define ATM_H

#include<bits/stdc++.h>
#include "Denomination.h"
#include "Withdraw.h"
#include "AtmMoneyException.h"
using namespace std;

class ATM {
private:
    map<int, Denomination> denominations;
    ATM();

public:
    static ATM &getInstance();
    void addMoney(int value, int count);
    Withdraw withdraw(int amount);
    void displayBalance() ;
    void Demonitization(int value);

private:
    bool isMultipleOfDenominations(int amount) ;
    int getTotalBalance() ;
    vector<int> SortedDenomination() ;
};

#endif