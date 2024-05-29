#include <bits/stdc++.h>;
using namespace std;

class Inverter
{
    // abstraction & encapsulation
protected:
    double current;
    double operatingVoltage;
    double powerRating;
    bool hasBattery;

public:
    Inverter(double current, double operatingVoltage, bool hasBattery)
        : current(current), operatingVoltage(operatingVoltage), hasBattery(hasBattery)
    {
        powerRating = current * operatingVoltage;
    }

    double getPowerRating()
    {
        return powerRating;
    }

    bool hasBatteryFunction()
    {
        return hasBattery;
    }

    virtual bool isSolar() = 0; // polymorphism

    virtual ~Inverter() {}
};

class SolarPanel
{
    double capacity;

public:
    SolarPanel(double capacity) : capacity(capacity) {}
    double getCapacity() { return capacity; }
};

class SolarInverter : public Inverter // hierarchial inheritence
{
protected:
    SolarPanel *panel; // association & aggregation
    bool gridOnSystem;

public:
    SolarInverter(double current, double operatingVoltage, bool hasBattery, SolarPanel *panel, bool gridOnSystem)
        : Inverter(current, operatingVoltage, hasBattery), panel(panel), gridOnSystem(gridOnSystem) {}

    bool isSolar() override // polymorphism
    {
        return true;
    }

    bool hasGridOnSystem()
    {
        return gridOnSystem;
    }

    ~SolarInverter()
    {
        delete panel;
    }
};

class NonSolarInverter : public Inverter // hierarchial inheritence
{
public:
    NonSolarInverter(double current, double operatingVoltage, bool hasBattery)
        : Inverter(current, operatingVoltage, hasBattery) {}

    bool isSolar() override // polymorphism
    {
        return false;
    }
};

class PCU : public SolarInverter // hierarchial inheritence
{
public:
    PCU(double current, double operatingVoltage, SolarPanel *panel)
        : SolarInverter(current, operatingVoltage, true, panel, false) {}
};

class GTI : public SolarInverter //  hierarchial inheritence
{
public:
    GTI(double current, double operatingVoltage, SolarPanel *panel)
        : SolarInverter(current, operatingVoltage, false, panel, true) {}
};

class Regalia : public SolarInverter // hierarchial inheritence
{
public:
    Regalia(double current, double operatingVoltage, SolarPanel *panel)
        : SolarInverter(current, operatingVoltage, false, panel, false) {}
};

class Zelio : public NonSolarInverter // hierarchial inheritence
{
public:
    Zelio(double current, double operatingVoltage)
        : NonSolarInverter(current, operatingVoltage, true) {}
};

class iCruze : public NonSolarInverter // hierarchial inheritence
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
