#include "Reservoir.h"
#include <utility>

Reservoir::ReservoirsMap Reservoir::reservoirsMap;

Reservoir::Reservoir(std::string name, std::string municipality, int id, std::string code, double maxDelivery) :
                     name(std::move(name)), municipality(std::move(municipality)), id(id),
                     code(std::move(code)), maxDelivery(maxDelivery) {
}


//TODO
Reservoir::~Reservoir() = default;

bool Reservoir::addReservoir(Reservoir* reservoir) {

    if (reservoirsMap.find(reservoir->code) != reservoirsMap.end()) {
        return false;
    }

    reservoirsMap.emplace(reservoir->code, reservoir);
    return true;
}

//TODO
bool Reservoir::removeReservoir(Reservoir *reservoir) {
    delete reservoir;
    return true;
}

Reservoir* Reservoir::getReservoir(const std::string &code) {

    auto it = reservoirsMap.find(code);

    if (it == reservoirsMap.end()) return nullptr;

    return it->second;
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

std::string Reservoir::getCode() const
{
    return this->code;
}

double Reservoir::getMaxDelivery() const
{
    return this->maxDelivery;
}

Reservoir::ReservoirsMap Reservoir::getReservoirsMap() {
    return reservoirsMap;
}


