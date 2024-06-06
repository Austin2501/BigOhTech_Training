#include "AudioMessage.h"
#include <bits/stdc++.h>
using namespace std;

void AudioMessage::sendMessage(const string &audioFile) {
    this->audioFile = audioFile;
    cout << "Audio Message Sent: " << audioFile << endl;
}
