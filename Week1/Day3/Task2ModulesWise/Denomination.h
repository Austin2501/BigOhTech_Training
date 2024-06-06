#ifndef DENOMINATION_H
#define DENOMINATION_H

class Denomination {
public:
    int value;
    int count;

    // Default constructor
    Denomination() : value(0), count(0) {}

    // Parameterized constructor
    Denomination(int value, int count) : value(value), count(count) {}
};

#endif 
