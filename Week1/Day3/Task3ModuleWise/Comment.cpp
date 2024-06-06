#include "Comment.h"

Comment::Comment(const std::string& text, const std::string& author) : text(text), author(author) {}

std::string Comment::getText() const {
    return text;
}

std::string Comment::getAuthor() const {
    return author;
}
