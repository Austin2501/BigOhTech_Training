#ifndef IMAGESTATUS_H
#define IMAGESTATUS_H

#include "IStatus.h"
using namespace std;

class ImageStatus : public IStatus {
private:
    string imageFile;

public:
    void postStatus(const string &imageFile) override;
};

#endif
