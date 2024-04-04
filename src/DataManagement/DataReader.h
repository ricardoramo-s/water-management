#ifndef WATER_MANAGEMENT_DATAREADER_H
#define WATER_MANAGEMENT_DATAREADER_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>

#include "../BaseClasses/City.h"
#include "../BaseClasses/Pipe.h"
#include "../BaseClasses/Pump.h"
#include "../BaseClasses/Reservoir.h"

class DataReader {

public:

    DataReader(std::string path, std::string name);


private:


    void readCities();
    void readPipes();
    void readReservoirs();
    void readStations();

    std::string path;
    std::string name;

};


#endif
