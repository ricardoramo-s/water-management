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

    /**
    * @brief Constructor.
    * reads the files and assign each read object to the right map
    * @param path The path to the directory containing the data files.
    * @param name The name (extension) of the flies.
     * @complexity O(n1 + n2 + n3 + n4)
     * @complexity n1 = number of lines in cities
     * @complexity n2 = number of lines in pipes
     * @complexity n3 = number of lines in reservoirs
     * @complexity n4 = number of lines in stations
    */
    DataReader(std::string path, std::string name);


private:


    /**
     * @brief Reads city data from file.
     * @complexity O(n)
     * @complexity n = number of lines
     */
    void readCities();

    /**
     * @brief Reads pipe data from file.
     * @complexity O(n)
     * @complexity n = number of lines
     */
    void readPipes();

    /**
     * @brief Reads reservoir data from file.
     * @complexity O(n)
     * @complexity n = number of lines
     */
    void readReservoirs();

    /**
     * @brief Reads pump data from file.
     * @complexity O(n)
     * @complexity n = number of lines
     */
    void readStations();

    /**
     * @brief The path to the directory containing the data files.
     */
    std::string path;

    /**
     * @brief The name (extension) of the files.
     */
    std::string name;

};


#endif
