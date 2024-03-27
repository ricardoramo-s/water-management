#include "City.h"

City::City(const std::string &name, const int &id, const std::string &code,
           const int &demand, const std::string &population)
{
    this->name = name;
    this->id = id;
    this->code = code;
    this->demand = demand;
    this->population = population;
}

std::string City::getName() const
{
    return this->name;
}

int City::getId() const
{
    return this->id;
}

std::string City::getcode() const
{
    return this->code;
}

int City::getDemand() const
{
    return this->demand;
}

std::string City::getPopulation() const
{
    return this->population;
}

void City::addCity(City *) {

}
