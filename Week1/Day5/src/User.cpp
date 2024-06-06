#include "User.h"
#include<bits/stdc++.h>
using namespace std;

User::User(const std::string &name, const std::string &phoneNumber)
    : name(name), phoneNumber(phoneNumber) {}

void User::addContact(const std::shared_ptr<Contact> &contact) {
    contacts.push_back(contact);
}

std::vector<std::shared_ptr<Contact>> User::getContacts() const {
    return contacts;
}

std::string User::getName() const {
    return name;
}

std::string User::getPhoneNumber() const {
    return phoneNumber;
}
