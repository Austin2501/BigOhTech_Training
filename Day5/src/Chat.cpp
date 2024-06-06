#include "Chat.h"
#include<bits/stdc++.h>
using namespace std;

void Chat::sendMessage(const string &contact, const shared_ptr<IMessage> &message, const string &content) {
    message->sendMessage(content);
    chatHistory[contact].push_back(message);
}

vector<shared_ptr<IMessage> > Chat::getChatHistory(const string &contact) const {
    auto it = chatHistory.find(contact);
    if (it != chatHistory.end()) {
        return it->second;
    }
    return {};
}
