#ifndef USER_H
#define USER_H

#include "Contact.h"
#include <bits/stdc++.h>
using namespace std;

class User {
private:
    string name;
    string phoneNumber;
    vector<shared_ptr<Contact> > contacts;

public:
    User(const string &name, const string &phoneNumber);

    void addContact(const shared_ptr<Contact> &contact);
    vector<shared_ptr<Contact> > getContacts() const;
    string getName() const;
    string getPhoneNumber() const;
};

#endif
