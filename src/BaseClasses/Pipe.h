#ifndef WATER_MANAGEMENT_PIPE_H
#define WATER_MANAGEMENT_PIPE_H

#include <string>
#include <unordered_map>
#include <vector>

class Pipe {

public:

    typedef std::unordered_map<std::string, std::vector<std::string>> pipesH;

private:

    std::string org;
    std::string dest;
    int capacity;
    bool direction;

};


#endif //WATER_MANAGEMENT_PIPE_H
