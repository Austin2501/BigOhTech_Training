#include "TextMessage.h"
#include<bits/stdc++.h>
using namespace std;

void TextMessage::sendMessage(const string &content) {
    this->content = content;
    cout << "Text Message Sent: " << content << endl;
}
