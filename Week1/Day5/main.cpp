#include "include/User.h"
#include "include/Chat.h"
#include "include/TextMessage.h"
#include "include/AudioMessage.h"
#include "include/VideoMessage.h"
#include "include/StatusManager.h"
#include "include/TextStatus.h"
#include "include/ImageStatus.h"
#include<bits/stdc++.h>
using namespace std;

int main() {
    // Create users
    auto user1 = make_shared<User>("Vineet", "123456789");
    auto user2 = make_shared<User>("Sagar", "987654321");

    // Add contacts
    user1->addContact(make_shared<Contact>("Sagar", "987654321"));
    user2->addContact(make_shared<Contact>("Vineet", "123456789"));

    // Messaging
    Chat chat;
    auto textMessage = make_shared<TextMessage>();
    chat.sendMessage("Sagar", textMessage, "Hello Vineet!");

    auto audioMessage = make_shared<AudioMessage>();
    chat.sendMessage("Sagar", audioMessage, "audio_file_path");

    auto videoMessage = make_shared<VideoMessage>();
    chat.sendMessage("Sagar", videoMessage, "video_file_path");

    // Posting Status
    StatusManager statusManager;
    auto textStatus = make_shared<TextStatus>();
    statusManager.postStatus("Vineet", textStatus, "Feeling happy!");

    auto imageStatus = make_shared<ImageStatus>();
    statusManager.postStatus("Vineet", imageStatus, "image_file_path");

    return 0;
}
