#include <bits/stdc++.h>;
using namespace std;

enum class typesOfVechicle
{
    car,
    truck,
    van,
    motercycle,
    electricVechicle
};

enum class typesOfParking
{
    compactSpot,
    largeSpot,
    handicappedSpot,
    motorcycleSpot,
    electricSpot
};

class Vehicle
{
protected:
    string name;
    typesOfVechicle types;

public:
    Vehicle(string name, typesOfVechicle types) : name(name), types(types) {}

    string getName()
    {
        return name;
    }

    typesOfVechicle getType()
    {
        return types;
    }
};

class Car : public Vehicle
{
public:
    Car(string name) : Vehicle(name, typesOfVechicle :: car) {}
};

class Truck : public Vehicle
{
public:
    Truck(string name) : Vehicle(name, typesOfVechicle :: truck) {}
};

class Van : public Vehicle
{
    Van(string name) : Vehicle(name, typesOfVechicle :: truck){}
};

class Motercycle : public Vehicle{

};

class ElectricVehicle : public Vehicle{
    
};


class ParkingSystem
{
protected:

    vector<ParkingFloor *> floors;
    unordered_map<string, ParkingTicket *> activeTickets;
    int maxCapacity;

public:

    ParkingSystem(int capacity) : maxCapacity(capacity) {}
    void addFloor(ParkingFloor *floor) { floors.push_back(floor); }

    ParkingTicket *getTicket()
    {

    }

    void exitParking()
    {

    }
};

class ParkingFloor
{
    string name;
    unordered_map<int, ParkingSpot*> spots;

public:
    ParkingFloor(string n) : name(n) {}

    void addParkingSpot(ParkingSpot* spot) { spots[spot->getSpot()] = spot; }

    ParkingSpot* getFreeSpot() {

    }
    void displayFreeSpots() {

    }
};

class ParkingSpot
{
protected:
    int spot;
    typesOfParking spotType;
    bool occupiedStatus;
    Vehicle* vehicleType;

public:

ParkingSpot(int number, typesOfParking type) : spot(number), spotType(type), occupiedStatus(false), vehicleType(nullptr) {}

    bool addVechicle()
    {
    }
    bool removeVechicle()
    {
    }
    bool isSpotOccupied()
    {
    }
    typesOfParking getType() const
    {
        return spotType;
    }
    int getSpot() const
    {
        return spot;
    }
};

class ParkingTicket
{
protected:
    string ticket;
    time_t entryTime;
    time_t exitTime;
    int totalFees;
    bool isPaid;

public:

ParkingTicket(string number) : ticket(number), entryTime(time(0)), exitTime(0), totalFees(0), isPaid(false) {}

    void exit()
    {
        exitTime = time(0);
    }

    void fees()
    {
        double hoursParked = difftime(exitTime, entryTime) / 3600;
        totalFees = 4 + (hoursParked - 1) * 3.5;
    }

    void pay()
    {
        isPaid = true;
    }

    bool isTicPaid() const
    {
        return isPaid;
    }

    double getPrice() const
    {
        return totalFees;
    }

    string getTicket() const
    {
        return ticket;
    }
};

int main()
{
    ParkingSystem ps(100);
    ParkingFloor* pf = new ParkingFloor("1st Floor");
    ps.addFloor(pf);
    

    return 0;
}