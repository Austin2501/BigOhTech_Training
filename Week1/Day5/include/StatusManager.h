#ifndef STATUSMANAGER_H
#define STATUSMANAGER_H

#include "IStatus.h"
#include <bits/stdc++.h>
using namespace std;

class StatusManager {
private:
    unordered_map<string, vector<shared_ptr<IStatus> > > statusHistory;

public:
    void postStatus(const string &user, const shared_ptr<IStatus> &status, const string &content);
    vector<shared_ptr<IStatus> > getStatusHistory(const string &user) const;
};

#endif
