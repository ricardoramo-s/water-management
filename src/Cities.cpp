#include "Cities.h"

Cities::Cities(const std::string &name)
{
    this->name = name;
}

Cities::Cities(const std::string &name, const int &id,
               const std::string &code, const int &demand, const int &population)
{
    this->name = name;
    this->id = id;
    this->code = code;
    this->demand = demand;
    this->population = population;
}

std::string Cities::getName() const
{
    return this->name;
}

int Cities::getID() const
{
    return this->id;
}

std::string Cities::getcode() const
{
    return this->code;
}

int Cities::getDemand() const
{
    return this->demand;
}

int Cities::getPopulation() const
{
    return this->population;
}