#include "Wall.h"

Wall::Wall() {}

void Wall::addBrick(Brick* brick) {
    if (bricks.size() < 90) {
        bricks.push_back(brick);
    }
}

std::vector<Brick*> Wall::getBricks() const {
    return bricks;
}

bool Wall::isFull() const {
    return bricks.size() >= 90;
}
