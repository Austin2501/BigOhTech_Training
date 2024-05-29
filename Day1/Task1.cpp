#include <bits/stdc++.h>;
using namespace std;

class Person
{
protected:
    string name;

public:
    Person(string name) : name(name) {}
    virtual string getName() { return name; }
    virtual ~Person() {}
};

class Driver : public Person
{
public:
    Driver(string name) : Person(name) {}
};

class MP : public Person
{
protected:
    string constituency;
    double spendingLimit;
    double expenses;
    Driver *driver;

public:
    MP(string name, string constituency, double spendingLimit, Driver *driver)
        : Person(name), constituency(constituency), spendingLimit(spendingLimit), expenses(0), driver(driver) {}

    string getConstituency() { return constituency; }
    Driver *getDriver() { return driver; }
    bool exceedsSpendingLimit() { return expenses > spendingLimit; }
    void addExpense(double amount) { expenses += amount; }
    virtual bool isArrestable() { return exceedsSpendingLimit(); }
    virtual ~MP() {}
};

class Minister : public MP
{
public:
    Minister(string name, string constituency, Driver *driver)
        : MP(name, constituency, 1000000, driver) {}
    bool isArrestable() override { return exceedsSpendingLimit(); }
    virtual ~Minister() {}
};

class PM : public Minister
{
    Driver *aircraftDriver;

public:
    PM(string name, string constituency, Driver *carDriver, Driver *aircraftDriver)
        : Minister(name, constituency, carDriver), aircraftDriver(aircraftDriver)
    {
        spendingLimit = 10000000; // limit
    }

    Driver *getAircraftDriver() { return aircraftDriver; }
    bool isArrestable() override { return false; }

    bool givePermissionToArrest(Minister *minister)
    {
        return minister->exceedsSpendingLimit();
    }
    virtual ~PM() {}
};

class Commissioner
{
    PM *pm;

public:
    Commissioner(PM *pm) : pm(pm) {}

    bool canArrest(MP *mp)
    {
        if (dynamic_cast<PM *>(mp))
        {
            return false; // Can't arrest pm
        }
        else if (Minister *minister = dynamic_cast<Minister *>(mp))
        {
            return pm->givePermissionToArrest(minister); // see permission which set on exceeding limit
        }
        else
        {
            // all mp can be arrested
            return mp->isArrestable();
        }
    }
    virtual ~Commissioner() {}
};

int main()
{
    Driver carDriver("Car Driver");
    Driver aircraftDriver("Aircraft Driver");

    MP mp1("MP1", "Constituency1", 100000, &carDriver);
    Minister minister1("Minister1", "Constituency2", &carDriver);
    Minister minister2("Minister1", "Constituency2", &carDriver);
    PM pm("PM", "Constituency3", &carDriver, &aircraftDriver);

    // Adding expenses
    mp1.addExpense(50000);
    mp1.addExpense(60000);
    minister1.addExpense(2000000);
    minister2.addExpense(4000000);
    pm.addExpense(5000000);

    Commissioner commissioner(&pm);

    cout << "Can arrest MP: " << commissioner.canArrest(&mp1) << endl;
    cout << "Can arrest Minister: " << commissioner.canArrest(&minister1) << endl;
    cout << "Can arrest Minister: " << commissioner.canArrest(&minister2) << endl;
    cout << "Can arrest PM: " << commissioner.canArrest(&pm) << endl;

    return 0;
}
