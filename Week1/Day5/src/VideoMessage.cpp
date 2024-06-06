#include "VideoMessage.h"
#include<bits/stdc++.h>
using namespace std;

void VideoMessage::sendMessage(const string &videoFile) {
    this->videoFile = videoFile;
    cout << "Video Message Sent: " << videoFile << endl;
}
