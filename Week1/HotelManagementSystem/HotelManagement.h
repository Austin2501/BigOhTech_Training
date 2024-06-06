// HotelManagement.h
#pragma once
#include "RoomManagement.h"
#include "UserManagement.h"
#include <bits/stdc++.h>
using namespace std;

class Hotel
{
private:
    string name;
    Address location;
    int numberOfRooms;
    vector<string> facilities;
    bool isApproved;
    Person *User;

    vector<shared_ptr<Room>> rooms; // List of rooms in the hotel
public:
    Hotel(string name, Address location, int numberOfRooms, vector<string> facilities)
        : name(name), location(location), numberOfRooms(numberOfRooms), facilities(facilities), isApproved(false) {}

    void approveHotel() { isApproved = true; }
    bool getApprovalStatus() { return isApproved; }

    void updateDetails(string newName, Address newLocation, int newNumberOfRooms, vector<string> newFacilities)
    {
        if (Person *User = dynamic_cast<Administrator *>(User))
        {
            name = newName;
            location = newLocation;
            numberOfRooms = newNumberOfRooms;
            facilities = newFacilities;
        }
    }

    void addRoom(shared_ptr<Room> room)
    {
        if (Person *User = dynamic_cast<Administrator *>(User))
            rooms.push_back(room);
    }

    string getName() { return name; }
    Address getLocation() { return location; }
    int getNumberOfRooms() { return numberOfRooms; }
    vector<string> getFacilities() { return facilities; }
    vector<shared_ptr<Room>> getRooms() { return rooms; }

    bool matchesCriteria(string &criteria)
    {
        // Simple criteria matching implementation
        for (auto &facility : facilities)
        {
            if (facility.find(criteria) != string::npos)
            {
                return true;
            }
        }
        return false;
    }
};