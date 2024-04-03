#ifndef WATER_MANAGEMENT_PIPE_H
#define WATER_MANAGEMENT_PIPE_H

#include <string>
#include <unordered_map>
#include <vector>

#include "City.h"
#include "Pump.h"
#include "Reservoir.h"

class Pipe {

public:

    typedef std::unordered_map<std::string, std::vector<std::string>> PipesMap;

    Pipe() = default;
    Pipe(std::string org, std::string dest, int capacity, bool direction);
    ~Pipe();



private:

    PipesMap

    std::string org;
    std::string dest;
    int capacity;
    bool direction;

};


#endif //WATER_MANAGEMENT_PIPE_H
