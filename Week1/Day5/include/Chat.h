#ifndef CHAT_H
#define CHAT_H

#include "IMessage.h"
#include <bits/stdc++.h>
using namespace std;

class Chat {
private:
    unordered_map<string, vector<shared_ptr<IMessage> > > chatHistory;

public:
    void sendMessage(const string &contact, const shared_ptr<IMessage> &message, const string &content);
    vector<shared_ptr<IMessage> > getChatHistory(const string &contact) const;
};

#endif
