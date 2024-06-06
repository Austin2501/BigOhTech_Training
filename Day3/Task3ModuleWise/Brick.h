#ifndef BRICK_H
#define BRICK_H

#include <string>
#include <vector>

class User;
class Comment;

class Brick {
private:
    std::string caption;
    std::string message;
    User* owner;
    User* dedicatedTo;
    std::vector<Comment*> comments;
    int flags;
    bool visible;

public:
    Brick(const std::string& caption, const std::string& message, User* owner, User* dedicatedTo);
    std::string getCaption() const;
    std::string getMessage() const;
    User* getOwner() const;
    User* getDedicatedTo() const;
    void addComment(Comment* comment);
    std::vector<Comment*> getComments() const;
    void flag();
    bool isVisible() const;
};

#endif // BRICK_H
