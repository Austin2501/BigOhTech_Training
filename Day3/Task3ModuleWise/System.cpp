#include "System.h"
#include <iostream>
#include <unordered_map>

System::System() {}

System::~System() {
    for (auto user : users) {
        delete user;
    }
    for (auto country : countries) {
        delete country;
    }
}

void System::addUser(User* user) {
    users.push_back(user);
}

void System::addCountry(Country* country) {
    countries.push_back(country);
}

User* System::getUserByName(const std::string& name) const {
    for (auto user : users) {
        if (user->getName() == name) {
            return user;
        }
    }
    return nullptr;
}

void System::displayHottestUser() const {
    std::unordered_map<std::string, int> dedicationCount;
    for (const auto& user : users) {
        for (const auto& brick : user->getBricks()) {
            User* dedicatedTo = brick->getDedicatedTo();
            if (dedicatedTo) {
                dedicationCount[dedicatedTo->getName()]++;
            }
        }
    }

    std::string hottestUser;
    int maxDedications = 0;
    for (const auto& entry : dedicationCount) {
        if (entry.second > maxDedications) {
            maxDedications = entry.second;
            hottestUser = entry.first;
        }
    }

    std::cout << "Hottest User: " << hottestUser << " with " << maxDedications << " dedications." << std::endl;
}

void System::displayLonelyUser() const {
    std::unordered_map<std::string, int> dedicationCount;
    for (const auto& user : users) {
        for (const auto& brick : user->getBricks()) {
            User* dedicatedTo = brick->getDedicatedTo();
            if (dedicatedTo) {
                dedicationCount[dedicatedTo->getName()]++;
            }
        }
    }

    for (const auto& user : users) {
        if (dedicationCount[user->getName()] == 0) {
            std::cout << "Lonely User: " << user->getName() << std::endl;
        }
    }
}
