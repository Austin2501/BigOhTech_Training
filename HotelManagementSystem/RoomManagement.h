// RoomManagement.h
#pragma once
#include <bits/stdc++.h>
using namespace std;

enum class RoomStyle
{
    STANDARD,
    DELUXE,
    FAMILY_SUITE,
    BUSINESS_SUITE
};
enum class RoomStatus
{
    AVAILABLE,
    RESERVED,
    OCCUPIED,
    NOT_AVAILABLE,
    BEING_SERVICED,
    OTHER
};

class Room
{
private:
    int number;
    RoomStyle style;
    RoomStatus status;
    double price;
    bool isSmoking;

public:
    Room(int number, RoomStyle style, RoomStatus status, double price, bool isSmoking)
        : number(number), style(style), status(status), price(price), isSmoking(isSmoking) {}

    bool isRoomAvailable() { return status == RoomStatus::AVAILABLE; }
    void checkIn() { status = RoomStatus::OCCUPIED; }
    void checkOut() { status = RoomStatus::AVAILABLE; }

    int getNumber() { return number; }
    RoomStyle getStyle() { return style; }
    RoomStatus getStatus() { return status; }
    double getPrice() { return price; }
    bool getIsSmoking() { return isSmoking; }
};