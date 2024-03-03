#include "DataProcessor.h"

DataProcessor::DataProcessor()
{
    createStations();
    createReservoir();
    createCities();
    this->graph = originalGraph();
    //TODO create flow
}

void DataProcessor::createStations() {

    std::ifstream file;
    std::string currentLine, id, code;

    file.open("../SmallDataSet/Stations_Madeira.csv");
    getline(file, currentLine);

    while (getline(file,currentLine)){
        std::istringstream iss(currentLine);

        checkField(iss,id);
        checkField(iss,code);


        PumpingStation ps = PumpingStation(stoi(id), code);
        stations.push_back(ps);
    }
    file.close();
}
//TODO implement parsers for each class, includeing graph creator

