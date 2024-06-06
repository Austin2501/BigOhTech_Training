#include "Contact.h"
#include<bits/stdc++.h>
using namespace std;

Contact::Contact(const string &name, const string &phoneNumber)
    : name(name), phoneNumber(phoneNumber) {}

string Contact::getName() const {
    return name;
}

string Contact::getPhoneNumber() const {
    return phoneNumber;
}
