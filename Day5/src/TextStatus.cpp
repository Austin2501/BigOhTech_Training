#include "TextStatus.h"
#include<bits/stdc++.h>
using namespace std;

void TextStatus::postStatus(const string &content) {
    this->content = content;
    cout << "Text Status Posted: " << content << endl;
}
