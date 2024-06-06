// BookingManagement.h
#pragma once
#include "RoomManagement.h"
#include <bits/stdc++.h>
using namespace std;

enum class BookingStatus
{
    REQUESTED,
    PENDING,
    CONFIRMED,
    CHECKED_IN,
    CHECKED_OUT,
    CANCELLED,
    ABANDONED
};

class Booking
{
private:
    int bookingID;
    shared_ptr<Room> room;
    BookingStatus status;
    string startDate;
    string endDate;

public:
    Booking(int bookingID, shared_ptr<Room> room, BookingStatus status, string startDate, string endDate)
        : bookingID(bookingID), room(room), status(status), startDate(startDate), endDate(endDate) {}

    void confirmBooking() { status = BookingStatus::CONFIRMED; }
    void checkIn() { status = BookingStatus::CHECKED_IN; }
    void checkOut() { status = BookingStatus::CHECKED_OUT; }

    BookingStatus getStatus() { return status; }
    shared_ptr<Room> getRoom() { return room; }
};