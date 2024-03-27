#ifndef WATER_MANAGEMENT_DATAREADER_H
#define WATER_MANAGEMENT_DATAREADER_H

#include <string>

class DataReader {

public:

    DataReader(std::string path, std:: string name);


private:


    void readCities();
    void readPipes();
    void readReservoirs();
    void readStations();

    std::string path;
    std::string name;

};


#endif
