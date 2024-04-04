#include "Pipe.h"

Pipe::PipesMultiMap Pipe::pipesMultiMap;

bool Pipe::PipesMultiMap::addRtPPipe(Pipe* pipe) {

    if (RtPMap.find(makeKey(pipe)) != RtPMap.end()) {
        return false;
    }

    RtPMap.emplace(makeKey(pipe), pipe);
    return true;
}

bool Pipe::PipesMultiMap::addPtPPipe(Pipe* pipe) {
    if (PtPMap.find(makeKey(pipe)) != PtPMap.end()) {
        return false;
    }

    PtPMap.emplace(makeKey(pipe), pipe);
    return true;
}

bool Pipe::PipesMultiMap::addPtCPipe(Pipe* pipe) {
    if (PtCMap.find(makeKey(pipe)) != PtCMap.end()) {
        return false;
    }

    PtCMap.emplace(makeKey(pipe), pipe);
    return true;
}

Pipe::PipesMap Pipe::PipesMultiMap::getPtCMAP() {
    return PtCMap;
}

Pipe::PipesMap Pipe::PipesMultiMap::getPtPMAP() {
    return PtPMap;
}

Pipe::PipesMap Pipe::PipesMultiMap::getRtPMAP() {
    return RtPMap;
}



Pipe::Pipe(std::string org, std::string dest, int capacity, bool direction) {
    this->org = org;
    this->dest = dest;
    this->capacity = capacity;
    this->direction = direction;
}

//todo
Pipe::~Pipe() = default;

bool Pipe::addPipe(Pipe* pipe) {

    int n = 0;

    if (!selectMap(makeKey(pipe), n)) return false;

    switch (n) {

        case 0:
            if (pipesMultiMap.addRtPPipe(pipe)) return true;
            break;
        case 1:
            if (pipesMultiMap.addPtPPipe(pipe)) return true;
            break;
        case 2:
            if (pipesMultiMap.addPtCPipe(pipe)) return true;
            break;
    }

    return false;
}

Pipe* Pipe::getPipe(Pipe::Key key) {

    int n = 0;

    if (!selectMap(key, n)) return nullptr;

    switch (n) {

        case 0: {
            auto it = pipesMultiMap.getRtPMAP().find(key);
            if (it == pipesMultiMap.getRtPMAP().end()) return nullptr;
            return it->second; }

        case 1: {
            auto it = pipesMultiMap.getPtPMAP().find(key);
            if (it == pipesMultiMap.getPtPMAP().end()) return nullptr;
            return it->second; }

        case 2: {
            auto it = pipesMultiMap.getPtCMAP().find(key);
            if (it == pipesMultiMap.getPtCMAP().end()) return nullptr;
            return it->second; }
    }

    return nullptr;
}

std::string Pipe::getOrg() const {
    return org;
}

std::string Pipe::getDest() const {
    return dest;
}

int Pipe::getCapacity() const {
    return capacity;
}

bool Pipe::getDirection() const {
    return direction;
}


Pipe::PipesMultiMap Pipe::getPipesMultiMap() {
    return pipesMultiMap;
}

bool Pipe::selectMap(Pipe::Key key, int &n) {

    if (key.first.substr(0, 2) == "R_") {
        n = 0;
        return true;
    }

    if (key.first.substr(0, 3) == "PS_" && key.second.substr(0, 3) == "PS_") {
        n = 1;
        return true;
    }

    if (key.second.substr(0, 2) == "C_") {
        n = 2;
        return true;
    }

    return false;

}

Pipe::Key Pipe::makeKey(Pipe* pipe) {
    Key key = std::make_pair(pipe->org, pipe->dest);
    return key;
}


