#ifndef SYSTEM_H
#define SYSTEM_H

#include "Country.h"
#include "User.h"
#include <vector>

class System {
private:
    std::vector<User*> users;
    std::vector<Country*> countries;

public:
    System();
    ~System();
    void addUser(User* user);
    void addCountry(Country* country);
    User* getUserByName(const std::string& name) const;
    void displayHottestUser() const;
    void displayLonelyUser() const;
};

#endif // SYSTEM_H
