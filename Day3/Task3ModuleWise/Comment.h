#ifndef COMMENT_H
#define COMMENT_H

#include <string>

class Comment {
private:
    std::string text;
    std::string author;

public:
    Comment(const std::string& text, const std::string& author);
    std::string getText() const;
    std::string getAuthor() const;
};

#endif // COMMENT_H
