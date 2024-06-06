#include "Brick.h"
#include "User.h"
#include "Comment.h"

Brick::Brick(const std::string& caption, const std::string& message, User* owner, User* dedicatedTo)
    : caption(caption), message(message), owner(owner), dedicatedTo(dedicatedTo), flags(0), visible(true) {}

std::string Brick::getCaption() const {
    return caption;
}

std::string Brick::getMessage() const {
    return message;
}

User* Brick::getOwner() const {
    return owner;
}

User* Brick::getDedicatedTo() const {
    return dedicatedTo;
}

void Brick::addComment(Comment* comment) {
    comments.push_back(comment);
}

std::vector<Comment*> Brick::getComments() const {
    return comments;
}

void Brick::flag() {
    flags++;
    if (flags > 10) {
        visible = false;
    }
}

bool Brick::isVisible() const {
    return visible;
}
