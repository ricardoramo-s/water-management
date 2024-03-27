//
// Created by bruno on 20/03/2024.
//

#include "Pump.h"

Pump::Pump(const int &id, const std::string &code) {
    this->id = id;
    this->code = code;
}

int Pump::getID() const {
    return id;
}

std::string Pump::getCode() const {
    return code;
}
