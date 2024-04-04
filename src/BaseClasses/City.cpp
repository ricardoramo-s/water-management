#include "City.h"
#include <utility>

City::CitiesMap City::citiesMap;

City::City(std::string name, int id, std::string code, double demand,
           std::string population) :
           name(std::move(name)), id(id), code(std::move(code)), demand(demand),
           population(std::move(population)) {

}

//TODO
City::~City() = default;

bool City::addCity(City* city) {

    if (citiesMap.find(city->code) != citiesMap.end()) {
        return false;
    }

    citiesMap.emplace(city->code, city);
    return true;
}

//TODO
bool City::removeCity(City *city) {
    delete city;
    return true;
}

City* City::getCity(const std::string& code) {

    auto it = citiesMap.find(code);

    if (it == citiesMap.end()) return nullptr;

    return it->second;
}


std::string City::getName() const {
    return this->name;
}

int City::getId() const {
    return this->id;
}

std::string City::getcode() const {
    return this->code;
}

double City::getDemand() const {
    return this->demand;
}

std::string City::getPopulation() const {
    return this->population;
}

City::CitiesMap City::getCitiesMap() {
    return citiesMap;
}








