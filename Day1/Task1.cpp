#include <bits/stdc++.h>
using namespace std;

// Base class for vehicles
class Vehicle
{
protected:
    string type;

public:
    Vehicle(string type) : type(type) {}
    virtual string getType() { return type; }
    virtual ~Vehicle() {}
};

// Derived classes for specific vehicle types
class Car : public Vehicle
{
public:
    Car() : Vehicle("Car") {}
};

class Aircraft : public Vehicle
{
public:
    Aircraft() : Vehicle("Aircraft") {}
};

// Class for person
class Person
{
protected:
    string name;

public:
    Person(string name) : name(name) {}
    virtual string getName() { return name; }
    virtual ~Person() {}
};

// Deriving Driver class from person
class Driver : public Person
{
public:
    Driver(string name) : Person(name) {}
};

// Deriving class MP from Person
class MP : public Person
{
protected:
    string constituency;
    double spendingLimit;
    double expenses;
    Car *car;
    Driver *driver;

public:
    MP(string name, string constituency, double spendingLimit, Car *car, Driver *driver)
        : Person(name), constituency(constituency), spendingLimit(spendingLimit), expenses(0), car(car), driver(driver) {}

    string getConstituency() { return constituency; }
    Car *getCar() { return car; }
    Driver *getDriver() { return driver; }
    bool exceedsSpendingLimit() { return expenses > spendingLimit; }
    void addExpense(double amount) { expenses += amount; }
    virtual bool isArrestable() { return exceedsSpendingLimit(); }
    virtual ~MP() {}
};

// Deriving class Minister from MP
class Minister : public MP
{
public:
    Minister(string name, string constituency, Car *car, Driver *driver)
        : MP(name, constituency, 1000000, car, driver) {}
    bool isArrestable() override { return exceedsSpendingLimit(); }
    virtual ~Minister() {}
};

// Deriving class PM from Minister
class PM : public Minister
{
    Aircraft *aircraft;
    Driver *aircraftDriver;

public:
    PM(string name, string constituency, Car *car, Driver *carDriver, Aircraft *aircraft, Driver *aircraftDriver)
        : Minister(name, constituency, car, carDriver), aircraft(aircraft), aircraftDriver(aircraftDriver)
    {
        spendingLimit = 10000000;
    }

    Aircraft *getAircraft() { return aircraft; }
    Driver *getAircraftDriver() { return aircraftDriver; }
    bool isArrestable() override { return false; }

    bool givePermissionToArrest(Minister *minister)
    {
        return minister->exceedsSpendingLimit();
    }

    virtual ~PM() {}
};

// Creating class Commissioner
class Commissioner
{
    PM *pm;

public:
    Commissioner(PM *pm) : pm(pm) {}

    bool canArrest(MP *mp)
    {
        if (dynamic_cast<PM *>(mp))
        {
            return false; // Can't arrest PM
        }
        else if (Minister *minister = dynamic_cast<Minister *>(mp))
        {
            return pm->givePermissionToArrest(minister); // See permission which set on exceeding limit
        }
        else
        {
            // All MP can be arrested
            return mp->isArrestable();
        }
    }

    virtual ~Commissioner() {}
};

int main()
{
    Driver carDriver("Car Driver");
    Driver aircraftDriver("Aircraft Driver");

    Car car;
    Aircraft aircraft;

    MP mp1("MP1", "Constituency1", 100000, &car, &carDriver);
    Minister minister1("Minister1", "Constituency2", &car, &carDriver);
    Minister minister2("Minister2", "Constituency2", &car, &carDriver);
    PM pm("PM", "Constituency3", &car, &carDriver, &aircraft, &aircraftDriver);

    // Adding expenses
    mp1.addExpense(50000);
    mp1.addExpense(60000);
    minister1.addExpense(2000000);
    minister2.addExpense(4000000);
    pm.addExpense(5000000);

    Commissioner commissioner(&pm);

    cout << "Can arrest MP: " << commissioner.canArrest(&mp1) << endl;
    cout << "Can arrest Minister1: " << commissioner.canArrest(&minister1) << endl;
    cout << "Can arrest Minister2: " << commissioner.canArrest(&minister2) << endl;
    cout << "Can arrest PM: " << commissioner.canArrest(&pm) << endl;

    return 0;
}
