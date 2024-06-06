#include <bits/stdc++.h>
using namespace std;

// Enums for vehicle types and parking spot types
enum class vehicleType
{
    car,
    truck,
    van,
    motorcycle,
    electricVehicle
};

enum class parkingType
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
    string Id;
    vehicleType type;

public:
    Vehicle(string Id, vehicleType type) : Id(Id), type(type) {}

    string getId() const { return Id; }
    vehicleType getType() const { return type; }
};

// Derived Vehicle classes
class Car : public Vehicle
{
public:
    Car(string Id) : Vehicle(Id, vehicleType::car) {}
};

class Truck : public Vehicle
{
public:
    Truck(string Id) : Vehicle(Id, vehicleType::truck) {}
};

class Van : public Vehicle
{
public:
    Van(string Id) : Vehicle(Id, vehicleType::van) {}
};

class Motorcycle : public Vehicle
{
public:
    Motorcycle(string Id) : Vehicle(Id, vehicleType::motorcycle) {}
};

class ElectricVehicle : public Vehicle
{
public:
    ElectricVehicle(string Id) : Vehicle(Id, vehicleType::electricVehicle) {}
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
        for (int i = 0; i < hoursParked; i++)
        {
            if (i < 1)
            {
                totalFee += 4;
            }
            else if (1 < i <= 2)
            {
                totalFee += 3.5;
            }
            totalFee += 2.5;
        }
    }

    void pay()
    {
        isPaid = true;
    }

    double getFee() const { return totalFee; }
    string getTicketNumber() const { return ticketNumber; }
};

// ParkingSpot class
class ParkingSpot
{
private:
    int number;
    parkingType type;
    bool occupied;
    Vehicle *vehicle;

public:
    ParkingSpot(int number, parkingType type) : number(number), type(type), occupied(false), vehicle(nullptr) {}

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
    parkingType getType() const { return type; }
    int getNumber() const { return number; }
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

    ParkingSpot *getFreeSpot(parkingType type)
    {
        for (auto &spot : spots)
        {
            if (spot.second->getType() == type && !spot.second->isOccupied())
            {
                return spot.second;
            }
        }
        return nullptr;
    }

    void displayFreeSpots()
    {
        for (auto &spot : spots)
        {
            if (!spot.second->isOccupied())
            {
                cout << "Free spot: " << spot.first << " Type: " << static_cast<int>(spot.second->getType()) << endl;
            }
        }
    }
};

// ParkingSystem class (Singleton)
class ParkingSystem
{
private:
    vector<ParkingFloor *> floors;
    unordered_map<string, ParkingTicket *> activeTickets;
    int maxCapacity;
    UserManagement *User;

public:
    static ParkingSystem &getInstance(int capacity = 100)
    {
        static ParkingSystem instance(capacity);
        return instance;
    }

    ParkingSystem(int capacity) : maxCapacity(capacity) {}

    void addFloor(ParkingFloor *floor)
    {   if(UserManagement *User = dynamic_cast<Admin *>(User))
            floors.push_back(floor);
    }

    ParkingTicket *generateTicket(Vehicle *vehicle)
    {
        if (activeTickets.size() >= maxCapacity)
        {
            cout << "Parking lot is full." << endl;
            return nullptr;
        }
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

class UserManagement {
private:
    string name;
    string id;
    UserManagement(){}
public:
    UserManagement(string name, string id) : name(name), id(id) {}
    virtual ~UserManagement() {}  
};

class Admin : public UserManagement{

    public:
    Admin();

};


// derived class from UserManagement
class Customer : public UserManagement
{
public:

    Customer(string name, string id) : UserManagement(name, id) {}
    ParkingTicket *requestTicket(Vehicle *vehicle)
    {
        return ParkingSystem::getInstance().generateTicket(vehicle);
    }

    void makePayment(ParkingTicket *ticket)
    {
        ticket->pay();
    }
};
// derived class from UserManagement
class ParkingAttendant : public UserManagement
{
public:
    ParkingAttendant(string name, string id) : UserManagement(name, id) {}

    ParkingTicket *generateTicketForCustomer(Vehicle *vehicle)
    {
        return ParkingSystem::getInstance().generateTicket(vehicle);
    }

    void receivePayment(ParkingTicket *ticket)
    {
        ticket->pay();
    }
};

int main()
{
    // Initialize parking lot with singleton
    ParkingSystem &system = ParkingSystem::getInstance(10);
    ParkingFloor *floor1 = new ParkingFloor("Floor 1");
    ParkingFloor *floor2 = new ParkingFloor("Floor 2");
    ParkingFloor *floor3 = new ParkingFloor("Floor 3");

    system.addFloor(floor1);
    system.addFloor(floor2);
    system.addFloor(floor3);

    // Add parking spots to the floor
    floor1->addParkingSpot(new ParkingSpot(1, parkingType::compactSpot));
    floor1->addParkingSpot(new ParkingSpot(2, parkingType::largeSpot));
    floor1->addParkingSpot(new ParkingSpot(3, parkingType::handicappedSpot));
    floor1->addParkingSpot(new ParkingSpot(4, parkingType::motorcycleSpot));
    floor1->addParkingSpot(new ParkingSpot(5, parkingType::electricSpot));

    // Display free spots
    floor1->displayFreeSpots();
    floor2->displayFreeSpots();
    floor3->displayFreeSpots();

    // Create a vehicle and get a parking ticket as a customer
    Car car1("ABC123");

    Customer customer("Vineet", "C1");
    ParkingTicket *ticket = customer.requestTicket(&car1);
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