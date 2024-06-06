#ifndef WALL_H
#define WALL_H

#include "Brick.h"
#include <vector>

class Wall {
private:
    std::vector<Brick*> bricks;

public:
    Wall();
    void addBrick(Brick* brick);
    std::vector<Brick*> getBricks() const;
    bool isFull() const;
};

#endif // WALL_H
