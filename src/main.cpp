#include "DataManagement/DataReader.h"

void printCity(City* city) {
    std::cout << city->getName() << "  " << city->getId() << "  " << city->getDemand() << "  " << city->getPopulation()
    << "  "  << city->getcode() << "\n";
}

void printReservoir(Reservoir* reservoir) {
    std::cout << reservoir->getName() << "  " << reservoir->getcode() << "  " << reservoir->getID() << "  "
    << reservoir->getMunicipality() << "  "  << reservoir->getMaxDelivery() << "\n";
}

void printPump(Pump* pump) {
    std::cout << pump->getCode() << "  " << pump->getID() << "\n";
}

void printPipes() {

    for (auto pipe : Pipe::getPipesMultiMap().getRtPMAP()) {
        std::cout << pipe.second->getOrg() << "  " << pipe.second->getDest() << "  " << pipe.second->getDirection() << "  "
        << pipe.second->getCapacity() << "\n";
    }
    for (auto pipe : Pipe::getPipesMultiMap().getPtPMAP()) {
        std::cout << pipe.second->getOrg() << "  " << pipe.second->getDest() << "  " << pipe.second->getDirection() << "  "
                  << pipe.second->getCapacity() << "\n";
    }
    for (auto pipe : Pipe::getPipesMultiMap().getPtCMAP()) {
        std::cout << pipe.second->getOrg() << "  " << pipe.second->getDest() << "  " << pipe.second->getDirection() << "  "
                  << pipe.second->getCapacity() << "\n";
    }
}

int main() {

    DataReader dataReader = DataReader(R"(C:\Users\bruno\Ambiente de Trabalho\Projects\water-management\SmallDataSet)", "_Madeira");

    City::CitiesMap citiesMap = City::getCitiesMap();

    for (auto city : citiesMap) {
        printCity(city.second);
    }

    std::cout << "\n\n";

    for (auto reservoir : Reservoir::getReservoirsMap()) {
        printReservoir(reservoir.second);
    }

    std::cout << "\n\n";

    for (auto pump : Pump::getPumpsMap()) {
        printPump(pump.second);
    }

    std::cout << "\n\n";

    printPipes();

    std::cout << Pipe::getPipesMultiMap().getRtPMAP().size();
}
