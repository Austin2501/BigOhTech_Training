#ifndef WITHDRAW_H
#define WITHDRAW_H

#include<bits/stdc++.h>
using namespace std;

class Withdraw {
public:
    map<int, int> notes;

    // Method to add notes
    void addNotes(int denomination, int count) {
        notes[denomination] += count;
    }

    // Method to display notes
    void display() {
        for ( auto &note : notes) {
            cout << note.first << " x " << note.second << endl;
        }
    }
};

#endif 