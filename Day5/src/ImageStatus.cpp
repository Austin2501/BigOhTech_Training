#include "ImageStatus.h"
#include<bits/stdc++.h>
using namespace std;

void ImageStatus::postStatus(const string &imageFile) {
    this->imageFile = imageFile;
    cout << "Image Status Posted: " << imageFile << endl;
}
