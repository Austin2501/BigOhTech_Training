#ifndef COUNTRY_H
#define COUNTRY_H

#include "City.h"
#include <string>
#include <vector>

class Country {
private:
    std::string name;
    std::vector<City*> cities;

public:
    Country(const std::string& name);
    std::string getName() const;
    void addCity(City* city);
    std::vector<City*> getCities() const;
    City* getCityByName(const std::string& cityName) const;
};

#endif // COUNTRY_H
