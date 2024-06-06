#ifndef AUDIOMESSAGE_H
#define AUDIOMESSAGE_H

#include "IMessage.h"
using namespace std;

class AudioMessage : public IMessage {
private:
    string audioFile;

public:
    void sendMessage(const string &audioFile) override;
};

#endif
