#ifndef WATER_MANAGEMENT_TEST_H
#define WATER_MANAGEMENT_TEST_H

#include <unordered_set>
#include "DataManagement/DataReader.h"

using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void printCities(City::CitiesMap citiesMap = City::getCitiesMap()) {

    for (auto city : citiesMap) {
        std::cout << city.second->getName() << "  " << city.second->getId() << "  " << city.second->getDemand() << "  "
        << city.second->getPopulation() << "  " << city.second->getCode() << "\n";
    }

    std::cout << "\n\n";
}

void printReservoirs(const Reservoir::ReservoirsMap& reservoirsMap = Reservoir::getReservoirsMap()) {

    for (const auto& reservoir : reservoirsMap) {
        std::cout << reservoir.second->getName() << "  " << reservoir.second->getCode() << "  "
        << reservoir.second->getID() << "  " << reservoir.second->getMunicipality() << "  "
        << reservoir.second->getMaxDelivery() << "\n";
    }

    std::cout << "\n\n";
}

void printPumps(const Pump::PumpsMap& pumpsMap = Pump::getPumpsMap()) {

    for (const auto& pump : pumpsMap) {
        std::cout << pump.second->getCode() << "  " << pump.second->getID() << "\n";
    }

    std::cout << "\n\n";
}

void printPipes(Pipe::PipesMultiMap pipesMultiMap = Pipe::getPipesMultiMap()) {

    for (auto pipe : pipesMultiMap.getRtPMAP()) {
        std::cout << pipe.second->getOrg() << "  " << pipe.second->getDest() << "  " << pipe.second->getDirection() << "  "
                  << pipe.second->getCapacity() << "\n";
    }
    for (auto pipe : pipesMultiMap.getPtPMAP()) {
        std::cout << pipe.second->getOrg() << "  " << pipe.second->getDest() << "  " << pipe.second->getDirection() << "  "
                  << pipe.second->getCapacity() << "\n";
    }
    for (auto pipe : pipesMultiMap.getPtCMAP()) {
        std::cout << pipe.second->getOrg() << "  " << pipe.second->getDest() << "  " << pipe.second->getDirection() << "  "
                  << pipe.second->getCapacity() << "\n";
    }

    std::cout << "\n\n";
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


string printSpaces(int n) {

    string space = "    ";
    string ret;

    for (int i = 0; i < n; i++) {
        ret += space;
    }

    return ret;
}

void printWithSpace(string str, int n) {

    string spaces = printSpaces(n);

    cout << spaces << str << "\n";
}

void printPath(const vector<string>& path, const Graph& graph) {

    string ret;

    for (const string& str : path) {
        ret += str + " -> ";
    }

    ret = ret.substr(0, ret.size() - 3);

    cout << '\n' << ret;
}

void dfsPath(Vertex* current, vector<string> currentPath, const Graph& graph, int i) {

    string code = current->getCode();
    currentPath.push_back(code);
    bool found = 0;

    for (auto edge : current->getAdj()) {
        auto it = find(currentPath.begin(), currentPath.end(), edge->getDest()->getCode());
        if (it == currentPath.end()) {
            found = 1;
            dfsPath(edge->getDest(), currentPath, graph, i++);
            //printWithSpace(code, i);
        }
    }

    if (!found) printPath(currentPath, graph);
}

void printGraph(const Graph& graph) {

    Vertex* source = graph.getSuperSource();
    vector<string> path;

    dfsPath(source, path, graph, 0);

}

void printVertexEdges(Vertex* vertex) {

    cout << vertex->getCode() << " [ ";

    for (auto edge : vertex->getAdj()) {
        cout << edge->getDest()->getCode() << " ";
    }

    cout << "]\n";

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void printSinkFlow(Graph* graph) {

    for (auto edge : graph->getSuperSink()->getIncoming()) {
        cout << "[" << edge->getOrig()->getCode() << "->(" << edge->getFlow() << "|" << edge->getWeight() << ")]  ";
    }
    cout << "\n\n";
}

void printSourceFlow(Graph* graph) {

    for (auto edge : graph->getSuperSource()->getAdj()) {
        cout << "[" << edge->getDest()->getCode() << "->(" << edge->getFlow() << "|" << edge->getWeight() << ")]  ";
    }
    cout << "\n\n";
}

#endif //WATER_MANAGEMENT_TEST_H
