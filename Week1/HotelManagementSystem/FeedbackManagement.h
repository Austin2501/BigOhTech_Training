// FeedbackManagement.h
#pragma once
#include <bits/stdc++.h>
using namespace std;

class Feedback
{
private:
    int feedbackID;
    string user;
    string comments;
    int rating;

public:
    Feedback(int feedbackID, string user, string comments, int rating)
        : feedbackID(feedbackID), user(user), comments(comments), rating(rating) {}
    int getRating() { return rating; }
    string getComments() { return comments; }
};