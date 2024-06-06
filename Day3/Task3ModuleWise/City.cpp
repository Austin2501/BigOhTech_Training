#include "City.h"

City::City(const std::string& name) : name(name) {}

std::string City::getName() const {
    return name;
}

void City::addWall(Wall* wall) {
    walls.push_back(wall);
}

std::vector<Wall*> City::getWalls() const {
    return walls;
}

Wall* City::getCurrentWall() const {
    if (walls.empty() || walls.back()->isFull()) {
        return nullptr;
    }
    return walls.back();
}
