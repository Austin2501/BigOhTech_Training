#ifndef ISTATUS_H
#define ISTATUS_H

#include <string>
using namespace std;

class IStatus {
public:
    virtual void postStatus(const string &content) = 0;
};

#endif
