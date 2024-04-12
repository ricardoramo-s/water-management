#ifndef WATER_MANAGEMENT_TEST_H
#define WATER_MANAGEMENT_TEST_H

#include <unordered_set>
#include "DataManagement/DataReader.h"
#include "DataManagement/DataManager.h"

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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void printAtoB(const vector<string>& path, const Graph& graph) {

    string ret;

    for (const string& str : path) {
        auto vertex = graph.findVertex(str);
        ret += vertex->getCode() + " -> ";
    }

    ret = ret.substr(0, ret.size() - 3);

    cout << '\n' << ret;
}

void dfsAtoB(Vertex* current, vector<string> currentPath, const Graph& graph, string& a, string& b) {

    string code = current->getCode();
    currentPath.push_back(code);

    for (auto edge : current->getAdj()) {
        auto it = find(currentPath.begin(), currentPath.end(), edge->getDest()->getCode());
        if (it == currentPath.end()) {
            dfsAtoB(edge->getDest(), currentPath, graph, a, b);
        }
    }

    if(currentPath[0] == a && currentPath.back() == b) printAtoB(currentPath, graph);
}

void printFromAtoB(const Graph& graph, string a, string b) {

    auto current = graph.findVertex(a);
    vector<string> path;

    dfsAtoB(current, path, graph, a, b);

    cout << "\n\n";
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


string printEdge(Edge* edge) {

    string ret;

    ret += edge->getOrig()->getCode() + "->" + edge->getDest()->getCode() + "(" + to_string((int) edge->getFlow())
            + "|" + to_string((int) edge->getWeight()) + ")";

    return ret;
}

void printEdges(Graph* graph) {

    vector<Edge*> vec = graph->getEdgeSet();

    std::sort(vec.begin(), vec.end(), [](const Edge* edge1, const Edge* edge2) {
        //return edge1->getOrig()->getCode() < edge2->getOrig()->getCode();
        //return edge2->getWeight() - edge2->getFlow() < edge1->getWeight() - edge1->getFlow();
        return edge1->getFlow() > edge2->getFlow();
    });

    for (auto edge : vec) {
        cout << printEdge(edge) << "\n";
    }
}

void printGraphVertexEdges(Graph* graph) {

    for (auto vertex : graph->getVertexSet()) {

        cout << "--- " << vertex->getCode() << " ---\n";

        cout << "|||IN:||||\n";

        for (auto edge : vertex->getIncoming()) {
            cout << printEdge(edge) << "\n";
        }

        cout << "\n|||Out:|||\n";

        for (auto edge : vertex->getAdj()) {
            cout << printEdge(edge) << "\n";
        }

        cout << "\n\n";
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


double getMaxFlow(Graph* graph) {

    double maxFlow = 0;

    for (auto vertex : graph->getSinkSet()) {
        for (auto edge : vertex->getAdj()) {
            maxFlow += edge->getFlow();
        }
    }

    cout << "Max Flow: " << maxFlow << "\n\n";

    return maxFlow;
}

void resetFlow(Graph* graph) {
    for (auto edge : graph->getEdgeSet()) {
        edge->setFlow(0);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


struct edgeHash {
    size_t operator()(const Edge* obj) const {
        size_t hash1 = hash<string>{}(obj->getOrig()->getCode());
        size_t hash2 = hash<string>{}(obj->getDest()->getCode());
        return hash1 ^ (hash2 << 8);
    }
};

struct vertexHash {
    size_t operator()(const Vertex* obj) const {
        size_t hash1 = hash<string>{}(obj->getCode());
        return hash1;
    }
};

typedef vector<unordered_set<Edge*, edgeHash>> PathsVector;
typedef unordered_set<Edge*, edgeHash> Path;
typedef unordered_set<Vertex*, vertexHash> Visited;


void explorePath(Vertex* current, Path path, Visited visited, PathsVector& pathsVector) {

    if (visited.find(current) != visited.end()) return;

    if (current->getCode() == "super_sink") {
        pathsVector.push_back(path);
        return;
    }

    visited.insert(current);

    for (auto edge : current->getAdj()) {
        auto it = path.insert(edge);
        explorePath(edge->getDest(), path, visited, pathsVector);
        path.erase(it.first);
    }
}


PathsVector exploreAllPaths(Graph* graph) {

    Vertex* start = graph->getSuperSource();

    Path path; Visited visited; PathsVector pathsVector;
    explorePath(start, path, visited, pathsVector);

    return pathsVector;
}

void printAllPaths(PathsVector& pathsVector) {

    for (auto a : pathsVector) {
        int n = 0;
        for(auto b : a) {
            if (n % 4 == 0) cout << "\n";
            cout << printEdge(b) << " || ";
            n++;
        }

        cout << "\n";
    }

    cout << "\n\n";
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


double calculateFlowDeviation(Graph* graph) {
    double totalFlow = 0.0;
    unsigned int numPipes = 0;

    // Calculate the total flow across all pipes
    for (Edge* edge : graph->getEdgeSet()) {
        totalFlow += edge->getFlow();
        numPipes++;
    }

    // Calculate the average flow
    double averageFlow = totalFlow / numPipes;

    // Calculate the deviation
    double deviation = 0.0;

    for (Edge* edge : graph->getEdgeSet()) {
        deviation += std::abs(edge->getFlow() - averageFlow);
    }

    return deviation;
}


unsigned int getBottleneck(Vertex* vertex) {
    unsigned int bottleneck = UINT_MAX;
    const Edge* edge = vertex->getPath();

    while (edge != nullptr) {


        // outgoing pipe
        if (edge->getDest() == vertex) {
            bottleneck = std::min(bottleneck, (unsigned) (edge->getWeight() - edge->getFlow()));
            vertex = edge->getOrig();
        }
            // incoming pipe
        else {
            bottleneck = std::min(bottleneck, (unsigned) edge->getFlow());
            vertex = edge->getDest();
        }

        // get the next pipe
        edge = vertex->getPath();
    }

    return bottleneck;
}


void balanceFlow(Graph* graph) {
    const double tolerance = 0.001; // Adjust this tolerance as needed
    double currentDeviation = calculateFlowDeviation(graph);

    std::vector<Edge*> edgeVec = graph->getEdgeSet();

    auto l = edgeVec.begin();
    auto r = edgeVec.end();

    std::sort(l, r, [](const Edge* edge1, const Edge* edge2) {
        return edge1->getFlow() > edge2->getFlow();
    });

    r--;

    graph->getSuperSink()->setPath(nullptr);

    // Iteratively adjust the flow until deviation is minimized
    while (currentDeviation > tolerance && l < r) {
        Edge* maxFlowPipe = *l;
        l++;

        Edge* minFlowPipe = *r;
        r--;

        unsigned int bottleneckToMaxPipe =  getBottleneck(maxFlowPipe->getOrig());

        unsigned int bottleneckToMinPipe = getBottleneck(minFlowPipe->getOrig());


        // Determine the transfer amount based on the smaller bottleneck
        int transferAmount = (int) std::min(bottleneckToMaxPipe, bottleneckToMinPipe);

        // Adjust flow in the pipes, ensuring transferAmount doesn't exceed minFlowPipe's capacity
        transferAmount = (int) std::min((int)transferAmount, (int)minFlowPipe->getWeight() - (int)minFlowPipe->getFlow());

        // Adjust flow in the pipes
        maxFlowPipe->setFlow(maxFlowPipe->getFlow() - transferAmount);
        minFlowPipe->setFlow(minFlowPipe->getFlow() + transferAmount);

        // Recalculate deviation
        double newDeviation = calculateFlowDeviation(graph);



        // If deviation increases, revert the flow adjustment
        if (newDeviation >= currentDeviation) {
            maxFlowPipe->setFlow(maxFlowPipe->getFlow() + transferAmount);
            minFlowPipe->setFlow(minFlowPipe->getFlow() -transferAmount);
            cout << "habibi";
            break; // No further improvement possible
        }

        currentDeviation = newDeviation;
    }
}


#endif //WATER_MANAGEMENT_TEST_H
