#include "Pump.h"
#include <utility>

Pump::PumpsMap Pump::pumpsMap;

Pump::Pump(int id, std::string code) :
        id(id), code(std::move(code)) {

    addPump(this);
}


//TODO
Pump::~Pump() = default;

bool Pump::addPump(Pump *pump) {

    if (pumpsMap.find(pump->code) != pumpsMap.end()) {
        return false;
    }

    pumpsMap.emplace(pump->code, pump);
    return true;
}

//TODO
bool Pump::removePump(Pump *pump) {
    delete pump;
    return true;
}

Pump *Pump::getPump(const std::string &code) {

    auto it = pumpsMap.find(code);

    if (it == pumpsMap.end()) return nullptr;

    return it->second;
}

int Pump::getID() const {
    return id;
}

std::string Pump::getCode() const {
    return code;
}


