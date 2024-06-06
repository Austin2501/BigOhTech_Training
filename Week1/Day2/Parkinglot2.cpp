#include<bits/stdc++.h>
using namespace std;


// VehicleType.h
enum class VehicleType {
    CAR = 1, TRUCK, ELECTRIC, VAN, MOTORBIKE
};

// ParkingSpotType.h
enum class ParkingSpotType {
    HANDICAPPED = 1, COMPACT, LARGE, MOTORBIKE, ELECTRIC
};

// AccountStatus.h
enum class AccountStatus {
    ACTIVE = 1, BLOCKED, BANNED, COMPROMISED, ARCHIVED, UNKNOWN
};

// Address.h
class Address {
private:
    string street_address;
    string city;
    string state;
    string zip_code;
    string country;

public:
    Address(string street, string city, string state, string zip_code, string country)
        : street_address(street), city(city), state(state), zip_code(zip_code), country(country) {}
};

// Person.h
class Person {
private:
    string name;
    Address address;
    string email;
    string phone;

public:
    Person(string name, Address address, string email, string phone)
        : name(name), address(address), email(email), phone(phone) {}
};

// Account.h
class Account {
protected:
    string user_name;
    string password;
    Person person;
    AccountStatus status;

public:
    Account(string user_name, string password, Person person, AccountStatus status = AccountStatus::ACTIVE)
        : user_name(user_name), password(password), person(person), status(status) {}

    virtual void reset_password() {}
};

// Admin.h
class Admin : public Account {
public:
    Admin(string user_name, string password, Person person, AccountStatus status = AccountStatus::ACTIVE)
        : Account(user_name, password, person, status) {}

    void add_parking_floor() {}
    void add_parking_spot() {}
};

// ParkingSpot.h
class ParkingSpot {
protected:
    int number;
    bool free;
    VehicleType vehicle_type;
    ParkingSpotType parking_spot_type;

public:
    ParkingSpot(int number, ParkingSpotType type) : number(number), parking_spot_type(type), free(true) {}

    bool is_free() const { return free; }
    int get_number() {return number;}
    void assign_vehicle(VehicleType vehicle) { free = false; vehicle_type = vehicle; }
    void remove_vehicle() { free = true; }
};

// ParkingFloor.h
class ParkingFloor {
private:
    string name;
    map<int, ParkingSpot*> spots;
    Account *Acc;

public:
    ParkingFloor(string name) : name(name) {}

    void add_parking_spot(ParkingSpot* spot) {
        if (Account *Acc = dynamic_cast<Admin *>(Acc))
            spots[spot->get_number()] = spot;
    }
};

// ParkingLot.h
class ParkingLot {
private:
    static ParkingLot* instance;
    std::string name;
    std::vector<ParkingFloor*> floors;

    ParkingLot(std::string name) : name(name) {}

public:
    static ParkingLot* get_instance(std::string name) {
        if (instance == nullptr) {
            instance = new ParkingLot(name);
        }
        return instance;
    }

    void add_floor(ParkingFloor* floor) {
        floors.push_back(floor);
    }
};

// Initialize static member
ParkingLot* ParkingLot::instance = nullptr;

// main.cpp
int main() {
    ParkingLot* lot = ParkingLot::get_instance("Downtown Parking");
    ParkingFloor* floor1 = new ParkingFloor("Floor 1");
    ParkingSpot* spot1 = new ParkingSpot(101, ParkingSpotType::COMPACT);

    floor1->add_parking_spot(spot1);
    lot->add_floor(floor1);

    return 0;
}