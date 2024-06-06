#ifndef IMESSAGE_H
#define IMESSAGE_H

#include <string>
using namespace std;

class IMessage {
public:
    virtual void sendMessage(const string &content) = 0;
};

#endif
