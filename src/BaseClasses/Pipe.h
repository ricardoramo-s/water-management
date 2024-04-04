#ifndef WATER_MANAGEMENT_PIPE_H
#define WATER_MANAGEMENT_PIPE_H


#include <string>
#include <unordered_map>
#include <vector>


#include "City.h"
#include "Pump.h"
#include "Reservoir.h"

class Pipe {

private:

    struct hash_pair {
        size_t operator()(const std::pair<std::string, std::string>& p) const
        {
            auto hash1 = std::hash<std::string>{}(p.first);
            auto hash2 = std::hash<std::string>{}(p.second);

            if (hash1 != hash2) {
                return hash1 ^ hash2;
            }

            return hash1;
        }
    };

public:

    typedef std::unordered_map<std::pair<std::string, std::string>, Pipe*, hash_pair> PipesMap; //org->dest : pipe
    typedef std::pair<std::string, std::string> Key;

    struct PipesMultiMap {

    public:
        Pipe* getPipe(Key key, int& n);
        bool addRtPPipe(Pipe*);
        bool addPtPPipe(Pipe*);
        bool addPtCPipe(Pipe*);
        PipesMap getRtPMAP();
        PipesMap getPtPMAP();
        PipesMap getPtCMAP();
    private:
        PipesMap RtPMap; //reservoir to pump
        PipesMap PtPMap; //pump to pump
        PipesMap PtCMap; //pump to city
    };


    Pipe() = default;
    Pipe(std::string org, std::string dest, int capacity, bool direction);
    ~Pipe();

    std::string getOrg() const;
    std::string getDest() const;
    int getCapacity() const;
    bool getDirection() const;

    static bool addPipe(Pipe* pipe);
    static Pipe* getPipe(Key key);
    static PipesMultiMap getPipesMultiMap();

private:

    static Key makeKey(Pipe* pipe);
    static bool selectMap(Key key, int& n); // 0-> RtP, 1->PtP, 2->PtC

    std::string org;
    std::string dest;
    int capacity = NULL;
    bool direction = NULL;

    static PipesMultiMap pipesMultiMap;
};


#endif //WATER_MANAGEMENT_PIPE_H
