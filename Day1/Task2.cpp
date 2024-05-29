#include <bits/stdc++.h>
using namespace std;

// Creating class for Inverter
class Inverter
{
protected:
    double current;
    double operatingVoltage;
    double powerRating;

public:
    Inverter(double current, double operatingVoltage)
        : current(current), operatingVoltage(operatingVoltage)
    {
        powerRating = current * operatingVoltage;
    }

    // Generating Power Rating function
    double getPowerRating()
    {
        return powerRating;
    }

    // Function to know if the inverter is solar
    virtual bool isSolar() = 0;

    // Destructor
    virtual ~Inverter() {}
};

// Class representing battery capability
class HasBattery
{
protected:
    bool hasBattery;

public:
    HasBattery(bool hasBattery) : hasBattery(hasBattery) {}

    bool hasBatteryFunction()
    {
        return hasBattery;
    }
};

// Class representing grid-tie capability
class HasGridOnSystem
{
protected:
    bool gridOnSystem;

public:
    HasGridOnSystem(bool gridOnSystem) : gridOnSystem(gridOnSystem) {}

    bool hasGridOnSystem()
    {
        return gridOnSystem;
    }
};

// Class for solar panel
class SolarPanel
{
    double capacity;

public:
    SolarPanel(double capacity) : capacity(capacity) {}
    double getCapacity() { return capacity; }
};

// Deriving class SolarInverter from Inverter and properties
class SolarInverter : public Inverter, public HasBattery, public HasGridOnSystem
{
protected:
    SolarPanel *panel;

public:
    SolarInverter(double current, double operatingVoltage, bool hasBattery, SolarPanel *panel, bool gridOnSystem)
        : Inverter(current, operatingVoltage), HasBattery(hasBattery), HasGridOnSystem(gridOnSystem), panel(panel) {}

    bool isSolar() override
    {
        return true;
    }

    ~SolarInverter()
    {
        delete panel;
    }
};

// Deriving class NonSolarInverter from Inverter and HasBattery
class NonSolarInverter : public Inverter, public HasBattery
{
public:
    NonSolarInverter(double current, double operatingVoltage, bool hasBattery)
        : Inverter(current, operatingVoltage), HasBattery(hasBattery) {}

    bool isSolar() override
    {
        return false;
    }
};

// Deriving class PCU from SolarInverter
class PCU : public SolarInverter
{
public:
    PCU(double current, double operatingVoltage, SolarPanel *panel)
        : SolarInverter(current, operatingVoltage, true, panel, false) {}
};

// Deriving class GTI from SolarInverter
class GTI : public SolarInverter
{
public:
    GTI(double current, double operatingVoltage, SolarPanel *panel)
        : SolarInverter(current, operatingVoltage, false, panel, true) {}
};

// Deriving class Regalia from SolarInverter
class Regalia : public SolarInverter
{
public:
    Regalia(double current, double operatingVoltage, SolarPanel *panel)
        : SolarInverter(current, operatingVoltage, false, panel, false) {}
};

// Deriving class Zelio from NonSolarInverter
class Zelio : public NonSolarInverter
{
public:
    Zelio(double current, double operatingVoltage)
        : NonSolarInverter(current, operatingVoltage, true) {}
};

// Deriving class iCruze from NonSolarInverter
class iCruze : public NonSolarInverter // Hierarchical inheritance
{
public:
    iCruze(double current, double operatingVoltage)
        : NonSolarInverter(current, operatingVoltage, true) {}
};

int main()
{
    SolarPanel *solarPanel1 = new SolarPanel(5000);
    SolarPanel *solarPanel2 = new SolarPanel(6000);
    SolarPanel *solarPanel3 = new SolarPanel(7000);

    PCU pcuInverter(10, 48, solarPanel1);
    GTI gtiInverter(15, 48, solarPanel2);
    Regalia regaliaInverter(20, 48, solarPanel3);
    Zelio zelioInverter(12, 48);
    iCruze icruzeInverter(18, 48);

    // Displaying information
    cout << "PCU Inverter Power Rating: " << pcuInverter.getPowerRating() << "W, Solar: " << pcuInverter.isSolar() << ", Has Battery: " << pcuInverter.hasBatteryFunction() << ", Grid On: " << pcuInverter.hasGridOnSystem() << endl;

    cout << "GTI Inverter Power Rating: " << gtiInverter.getPowerRating() << "W, Solar: " << gtiInverter.isSolar() << ", Has Battery: " << gtiInverter.hasBatteryFunction() << ", Grid On: " << gtiInverter.hasGridOnSystem() << endl;

    cout << "Regalia Inverter Power Rating: " << regaliaInverter.getPowerRating() << "W, Solar: " << regaliaInverter.isSolar() << ", Has Battery: " << regaliaInverter.hasBatteryFunction() << ", Grid On: " << regaliaInverter.hasGridOnSystem() << endl;

    cout << "Zelio Inverter Power Rating: " << zelioInverter.getPowerRating() << "W, Solar: " << zelioInverter.isSolar() << ", Has Battery: " << zelioInverter.hasBatteryFunction() << endl;

    cout << "iCruze Inverter Power Rating: " << icruzeInverter.getPowerRating() << "W, Solar: " << icruzeInverter.isSolar() << ", Has Battery: " << icruzeInverter.hasBatteryFunction() << endl;

    return 0;
}
