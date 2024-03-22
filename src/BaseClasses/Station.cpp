//
// Created by bruno on 20/03/2024.
//

#include "Station.h"

Station::Station(const int &id, const std::string &code) {
    this->id = id;
    this->code = code;
}

int Station::getID() const {
    return id;
}

std::string Station::getCode() const {
    return code;
}
