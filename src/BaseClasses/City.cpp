#include "City.h"
#include <utility>
#include "GraphClasses/StaticGraph.h"

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

std::string City::getCode() const {
    return this->code;
}

double City::getDemand() const {
    return this->demand;
}

double City::getFlow() const {
    Vertex* vertex = StaticGraph::graph_->findVertex(code);
    double flow = 0;

    for (auto edge : vertex->getIncoming()) {
        flow += edge->getFlow();
    }

    return flow;
}

std::string City::getPopulation() const {
    return this->population;
}

City::CitiesMap City::getCitiesMap() {
    return citiesMap;
}








