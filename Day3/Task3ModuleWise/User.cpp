#include "User.h"
#include "Brick.h"
#include <iostream>

User::User(const std::string& name) : name(name) {}

std::string User::getName() const {
    return name;
}

void User::addBrick(Brick* brick) {
    ownedBricks.push_back(brick);
}

std::vector<Brick*> User::getBricks() const {
    return ownedBricks;
}

void User::displayOwnedBricks() const {
    std::cout << name << "'s Bricks:" << std::endl;
    for (auto brick : ownedBricks) {
        // Implement brick display logic
    }
}
