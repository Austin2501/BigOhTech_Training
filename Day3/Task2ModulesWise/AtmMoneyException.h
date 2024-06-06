#ifndef ATMMONEYEXCEPTION_H
#define ATMMONEYEXCEPTION_H

#include<bits/stdc++.h>
using namespace std;

// checking for balance less than amount needed
class InvalidBalanceAmountException : public runtime_error {
public:
    InvalidBalanceAmountException() : runtime_error("Insufficient balance!") {}
};

// checking if needed amount is in multiple of notes
class InvalidDenominationAmountException : public runtime_error {
public:
    InvalidDenominationAmountException() : runtime_error("Please give amount in multiple of denomination!") {}
};

#endif 