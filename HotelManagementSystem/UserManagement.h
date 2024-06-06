// UserManagement.h
#pragma once
#include <bits/stdc++.h>
using namespace std;

enum class AccountType
{
    NORMAL_USER,
    HOTEL_AGENT,
    ADMINISTRATOR
};
enum class AccountStatus
{
    ACTIVE,
    INACTIVE,
    PENDING_APPROVAL
};

class Address
{
public:
    string street, city, state, zip, country;
    Address(string street, string city, string state, string zip, string country)
        : street(street), city(city), state(state), zip(zip), country(country) {}
};

class Person
{
protected:
    string name;
    Address address;
    string email;
    string phone;

public:
    Person(string name, Address address, string email, string phone)
        : name(name), address(address), email(email), phone(phone) {}
    virtual ~Person() = default;
};

class User : public Person
{
private:
    AccountType accountType;
    AccountStatus accountStatus;

public:
    User(string name, Address address, string email, string phone, AccountType type)
        : Person(name, address, email, phone), accountType(type), accountStatus(AccountStatus::PENDING_APPROVAL) {}
    void updateDetails(string newEmail, string newPhone)
    {
        email = newEmail;
        phone = newPhone;
    }
    AccountType getAccountType() { return accountType; }
    AccountStatus getAccountStatus() { return accountStatus; }
    void setAccountStatus(AccountStatus status) { accountStatus = status; }
};

// NormalUser class
class NormalUser : public User
{
public:
    NormalUser(string name, Address address, string email, string phone)
        : User(name, address, email, phone, AccountType::NORMAL_USER) {}

    void searchHotels(const string &criteria)
    {
        // Implementation for searching hotels based on criteria
    }

    void bookRoom(int hotelId, int roomId)
    {
        // Implementation for booking a room
    }
};

// HotelAgent class
class HotelAgent : public User
{
public:
    HotelAgent(string name, Address address, string email, string phone)
        : User(name, address, email, phone, AccountType::HOTEL_AGENT) {}

    void addHotelDetails(const string &hotelName, const Address &hotelAddress, int numberOfRooms, const vector<string> &facilities)
    {
        // Implementation for adding hotel details
    }

    void updateHotelDetails(int hotelId, const string &hotelName, const Address &hotelAddress, int numberOfRooms, const vector<string> &facilities)
    {
        // Implementation for updating hotel details
    }
};

// Administrator class
class Administrator : public User
{
public:
    Administrator(string name, Address address, string email, string phone)
        : User(name, address, email, phone, AccountType::ADMINISTRATOR) {}

    void approveHotel(int hotelId)
    {
        // Implementation for approving hotel details
    }

    void deleteUser(int userId)
    {
        // Implementation for deleting a user
    }

    void deleteHotel(int hotelId)
    {
        // Implementation for deleting a hotel
    }
};