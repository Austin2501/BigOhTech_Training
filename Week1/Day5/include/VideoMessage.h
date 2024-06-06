#ifndef VIDEOMESSAGE_H
#define VIDEOMESSAGE_H

#include "IMessage.h"
using namespace std;

class VideoMessage : public IMessage {
private:
    string videoFile;

public:
    void sendMessage(const string &videoFile) override;
};

#endif
