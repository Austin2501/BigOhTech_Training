#include "UserManagement.h"
#include "HotelManagement.h"
#include "RoomManagement.h"
#include "BookingManagement.h"
#include "FeedbackManagement.h"
#include <bits/stdc++.h>
using namespace std;

int main()
{
    // Create Address
    Address hotelAddress("Noida Street", "City", "State", "Zip", "Country");

    // Create Hotel
    vector<string> facilities;
    facilities.push_back("WiFi");
    facilities.push_back("Pool");
    facilities.push_back("Gym");

    Hotel myHotel("Haldiram", hotelAddress, 100, facilities);

    // Create Room
    shared_ptr<Room> newRoom = make_shared<Room>(101, RoomStyle::DELUXE, RoomStatus::AVAILABLE, 150.0, false);

    // Add Room to Hotel
    myHotel.addRoom(newRoom);

    // Create Normal User
    NormalUser normalUser("Vineet", Address("Noida Street", "City", "Region", "12345", "Country"), "vineet@gmail.com", "1234567890");

    // Normal User searches for hotels
    normalUser.searchHotels("WiFi");

    // Normal User books a room
    normalUser.bookRoom(1, 101);

    // Create Hotel Agent
    HotelAgent hotelAgent("Ram Manohar", Address("Ghaziabad Street", "City", "State", "Zip", "Country"), "ram@gmail.com", "0987654321");

    // Hotel Agent adds hotel details
    vector<string>benefits;
    benefits.push_back("WiFi");
    benefits.push_back("Breakfast");
    
    hotelAgent.updateHotelDetails(1, "Sunrise Hotel", Address("321 Avenue", "City", "State", "Zip", "Country"), 50, benefits);

    // Create Administrator
    Administrator admin("Shyam Manohar", Address("Delhi Street", "City", "State", "Zip", "Country"), "shyam@gmail.com", "1122334455");

    // Administrator approves hotel
    admin.approveHotel(1);

    // Administrator deletes a user
    admin.deleteUser(1);

    // Administrator deletes a hotel
    admin.deleteHotel(1);

    // Create Booking
    Booking newBooking(1, newRoom, BookingStatus::REQUESTED, "2024-06-05", "2024-06-10");

    // Check-in Guest
    newBooking.checkIn();

    // Display Booking Status
    cout << "Booking Status: " << static_cast<int>(newBooking.getStatus()) << endl;

    return 0;
}