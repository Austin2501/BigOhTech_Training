#include <bits/stdc++.h>
using namespace std;

// Enums for vehicle types and parking spot types
enum class VehicleType
{
    car,
    truck,
    van,
    motorcycle,
    electricVehicle
};

enum class ParkingSpotType
{
    compactSpot,
    largeSpot,
    handicappedSpot,
    motorcycleSpot,
    electricSpot
};

// Base class for Vehicles
class Vehicle
{
protected:
    string licensePlate;
    VehicleType type;

public:
    Vehicle(string licensePlate, VehicleType type) : licensePlate(licensePlate), type(type) {}

    string getLicensePlate() const { return licensePlate; }
    VehicleType getType() const { return type; }
};

// Derived Vehicle classes
class Car : public Vehicle
{
public:
    Car(string licensePlate) : Vehicle(licensePlate, VehicleType::car) {}
};

class Truck : public Vehicle
{
public:
    Truck(string licensePlate) : Vehicle(licensePlate, VehicleType::truck) {}
};

class Van : public Vehicle
{
public:
    Van(string licensePlate) : Vehicle(licensePlate, VehicleType::van) {}
};

class Motorcycle : public Vehicle
{
public:
    Motorcycle(string licensePlate) : Vehicle(licensePlate, VehicleType::motorcycle) {}
};

class ElectricVehicle : public Vehicle
{
public:
    ElectricVehicle(string licensePlate) : Vehicle(licensePlate, VehicleType::electricVehicle) {}
};

// ParkingSpot class
class ParkingSpot
{
private:
    int number;
    ParkingSpotType type;
    bool occupied;
    Vehicle *vehicle;

public:
    ParkingSpot(int number, ParkingSpotType type) : number(number), type(type), occupied(false), vehicle(nullptr) {}

    bool parkVehicle(Vehicle *vehicle)
    {
        if (!occupied)
        {
            this->vehicle = vehicle;
            occupied = true;
            return true;
        }
        return false;
    }

    bool removeVehicle()
    {
        if (occupied)
        {
            vehicle = nullptr;
            occupied = false;
            return true;
        }
        return false;
    }

    bool isOccupied() const { return occupied; }
    ParkingSpotType getType() const { return type; }
    int getNumber() const { return number; }
};

// ParkingTicket class
class ParkingTicket
{
private:
    string ticketNumber;
    time_t entryTime;
    time_t exitTime;
    double totalFee;
    bool isPaid;

public:
    ParkingTicket(string number) : ticketNumber(number), entryTime(time(0)), exitTime(0), totalFee(0), isPaid(false) {}

    void markExit()
    {
        exitTime = time(0);
    }

    void calculateFee()
    {
        double hoursParked = difftime(exitTime, entryTime) / 3600;
        totalFee = 4 + (hoursParked - 1) * 3.5;
    }

    void pay()
    {
        isPaid = true;
    }

    double getFee() const { return totalFee; }
    string getTicketNumber() const { return ticketNumber; }
};

// ParkingFloor class
class ParkingFloor
{
private:
    string name;
    unordered_map<int, ParkingSpot *> spots;

public:
    ParkingFloor(string name) : name(name) {}

    void addParkingSpot(ParkingSpot *spot)
    {
        spots[spot->getNumber()] = spot;
    }

    ParkingSpot *getFreeSpot(ParkingSpotType type)
    {
        for (auto &spotPair : spots)
        {
            if (spotPair.second->getType() == type && !spotPair.second->isOccupied())
            {
                return spotPair.second;
            }
        }
        return nullptr;
    }

    void displayFreeSpots()
    {
        for (auto &spotPair : spots)
        {
            if (!spotPair.second->isOccupied())
            {
                cout << "Free spot: " << spotPair.first << " Type: " << static_cast<int>(spotPair.second->getType()) << endl;
            }
        }
    }
};

// ParkingSystem class
class ParkingSystem
{
private:
    vector<ParkingFloor *> floors;
    unordered_map<string, ParkingTicket *> activeTickets;
    int maxCapacity;

public:
    ParkingSystem(int capacity) : maxCapacity(capacity) {}

    void addFloor(ParkingFloor *floor)
    {
        floors.push_back(floor);
    }

    ParkingTicket *generateTicket(Vehicle *vehicle)
    {
        if (activeTickets.size() >= maxCapacity)
        {
            cout << "Parking lot is full." << endl;
            return nullptr;
        }
        // Generate a ticket number based on the current time
        string ticketNumber = to_string(time(0));
        ParkingTicket *ticket = new ParkingTicket(ticketNumber);
        activeTickets[ticketNumber] = ticket;
        return ticket;
    }

    void exitParking(string ticketNumber)
    {
        if (activeTickets.find(ticketNumber) != activeTickets.end())
        {
            ParkingTicket *ticket = activeTickets[ticketNumber];
            ticket->markExit();
            ticket->calculateFee();
            cout << "Total fee: $" << ticket->getFee() << endl;
            activeTickets.erase(ticketNumber);
        }
        else
        {
            cout << "Invalid ticket." << endl;
        }
    }
};

// User classes
class User
{
protected:
    string name;
    string id;

public:
    User(string name, string id) : name(name), id(id) {}
    virtual void printRole() = 0;
};

class Admin : public User
{
public:
    Admin(string name, string id) : User(name, id) {}

    void addParkingFloor(ParkingSystem &system, ParkingFloor *floor)
    {
        system.addFloor(floor);
    }

    void printRole() override
    {
        cout << "Role: Admin" << endl;
    }
};

class Customer : public User
{
public:
    Customer(string name, string id) : User(name, id) {}

    void printRole() override
    {
        cout << "Role: Customer" << endl;
    }

    ParkingTicket *requestTicket(ParkingSystem &system, Vehicle *vehicle)
    {
        return system.generateTicket(vehicle);
    }

    void makePayment(ParkingTicket *ticket)
    {
        ticket->pay();
    }
};

class ParkingAttendant : public User
{
public:
    ParkingAttendant(string name, string id) : User(name, id) {}

    void printRole() override
    {
        cout << "Role: Parking Attendant" << endl;
    }

    ParkingTicket *generateTicketForCustomer(ParkingSystem &system, Vehicle *vehicle)
    {
        return system.generateTicket(vehicle);
    }

    void receivePayment(ParkingTicket *ticket)
    {
        ticket->pay();
    }
};

int main()
{
    // Initialize parking lot
    ParkingSystem system(100);
    ParkingFloor *floor1 = new ParkingFloor("Floor 1");
    system.addFloor(floor1);

    // Add parking spots to the floor
    floor1->addParkingSpot(new ParkingSpot(1, ParkingSpotType::compactSpot));
    floor1->addParkingSpot(new ParkingSpot(2, ParkingSpotType::largeSpot));
    floor1->addParkingSpot(new ParkingSpot(3, ParkingSpotType::handicappedSpot));
    floor1->addParkingSpot(new ParkingSpot(4, ParkingSpotType::motorcycleSpot));
    floor1->addParkingSpot(new ParkingSpot(5, ParkingSpotType::electricSpot));

    // Display free spots
    floor1->displayFreeSpots();

    // Create a vehicle and get a parking ticket as a customer
    Car car1("ABC123");
    Customer customer("Vineet", "C1");
    ParkingTicket *ticket = customer.requestTicket(system, &car1);
    if (ticket)
    {
        cout << "Ticket issued: " << ticket->getTicketNumber() << endl;
    }

    // Simulate exiting the parking lot
    if (ticket)
    {
        system.exitParking(ticket->getTicketNumber());
    }

    return 0;
}
