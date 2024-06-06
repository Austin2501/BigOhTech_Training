#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include "IMessage.h"
using namespace std;

class TextMessage : public IMessage {
private:
    string content;

public:
    void sendMessage(const string &content) override;
};

#endif
