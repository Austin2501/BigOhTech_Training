#include "StatusManager.h"
#include<bits/stdc++.h>
using namespace std;

void StatusManager::postStatus(const string &user, const shared_ptr<IStatus> &status, const string &content) {
    status->postStatus(content);
    statusHistory[user].push_back(status);
}

vector<shared_ptr<IStatus>> StatusManager::getStatusHistory(const string &user) const {
    auto it = statusHistory.find(user);
    if (it != statusHistory.end()) {
        return it->second;
    }
    return {};
}
