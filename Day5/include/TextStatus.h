#ifndef TEXTSTATUS_H
#define TEXTSTATUS_H

#include "IStatus.h"
using namespace std;

class TextStatus : public IStatus {
private:
    string content;

public:
    void postStatus(const string &content) override;
};

#endif
