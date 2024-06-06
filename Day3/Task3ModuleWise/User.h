#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class Brick;

class User {
private:
    std::string name;
    std::vector<Brick*> ownedBricks;
public:
    User(const std::string& name);
    std::string getName() const;
    void addBrick(Brick* brick);
    std::vector<Brick*> getBricks() const;
    void displayOwnedBricks() const;
};

#endif // USER_H
