#include "ATM.h"
#include<bits/stdc++.h>

using namespace std;

ATM::ATM() {}

ATM& ATM::getInstance() {
    static ATM instance;
    return instance;
}

void ATM::addMoney(int value, int count) {
    if (denominations.find(value) != denominations.end()) {
        denominations[value].count += count;
    } else {
        denominations[value] = Denomination(value, count);
    }
}

Withdraw ATM::withdraw(int amount) {
    if (!isMultipleOfDenominations(amount)) {
        throw InvalidDenominationAmountException();
    }

    int totalBalance = getTotalBalance();
    if (amount > totalBalance) {
        throw InvalidBalanceAmountException();
    }

    Withdraw result;
    vector<int> keys = SortedDenomination();
    for (int key : keys) {
        int needed = amount / key;
        if (needed > 0 && denominations[key].count > 0) {
            int toGive = min(needed, denominations[key].count);
            amount -= toGive * key;
            denominations[key].count -= toGive;
            result.addNotes(key, toGive);
        }
    }

    if (amount > 0) {
        throw InvalidBalanceAmountException(); // should never reach here if logic is correct
    }

    return result;
}

void ATM::displayBalance()  {
    for ( auto &denomination : denominations) {
        cout << denomination.first << " INR : " << denomination.second.count << " notes" << endl;
    }
}

void ATM::Demonitization(int value) {
    if (denominations.find(value) != denominations.end()) {
        denominations.erase(value);
        cout << "Denomination " << value << " INR has been removed from the ATM." << endl;
    } else {
        cout << "Denomination " << value << " INR not found in the ATM." << endl;
    }
}

bool ATM::isMultipleOfDenominations(int amount)  {
    for ( auto &denomination : denominations) {
        if (amount % denomination.first == 0) {
            return true;
        }
    }
    return false;
}

int ATM::getTotalBalance()  {
    int total = 0;
    for ( auto &denomination : denominations) {
        total += denomination.first * denomination.second.count;
    }
    return total;
}

vector<int> ATM::SortedDenomination()  {
    vector<int> keys;
    for ( auto &denomination : denominations) {
        keys.push_back(denomination.first);
    }
    sort(keys.rbegin(), keys.rend());
    return keys;
}