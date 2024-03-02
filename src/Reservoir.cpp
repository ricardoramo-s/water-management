#include "Reservoir.h"

Reservoir::Reservoir(const std::string &name)
{
    this->name = name;
}

Reservoir::Reservoir(const std::string &name, const std::string &municipality,
                     const int &id, const std::string &code, const int &maxDelivery)
{
    this->name = name;
    this->municipality = municipality;
    this->id = id;
    this->code = code;
    this->maxDelivery = maxDelivery;
}

std::string Reservoir::getName() const
{
    return this->name;
}

std::string Reservoir::getMunicipality() const
{
    return this->municipality;
}

int Reservoir::getID() const
{
    return this->id;
}

std::string Reservoir::getcode() const
{
    return this->code;
}

int Reservoir::getMaxDelivery() const
{
    return this->maxDelivery;
}