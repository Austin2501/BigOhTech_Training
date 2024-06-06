#ifndef CITY_H
#define CITY_H

#include "Wall.h"
#include <string>
#include <vector>

class City {
private:
    std::string name;
    std::vector<Wall*> walls;

public:
    City(const std::string& name);
    std::string getName() const;
    void addWall(Wall* wall);
    std::vector<Wall*> getWalls() const;
    Wall* getCurrentWall() const;
};

#endif // CITY_H
