#ifndef WATER_MANAGEMENT_GRAPH_H
#define WATER_MANAGEMENT_GRAPH_H

#include <string>
#include <vector>
#include <unordered_set>
#include <list>
#include <queue>
#include <iostream>
#include <stack>
#include <cmath>
#include <thread>
#include <mutex>
#include <set>
#include <algorithm>
#include <climits>
#include <utility>
#include <immintrin.h>
#include "City.h"
#include "Reservoir.h"

#define nodeTID std::tuple<const std::string, const int>

class PumpingStations{
public:
    PumpingStations(const int &id, const std::string& code) : id(id), code(code) {};
    int getId() const {return this->id;}
    std::string getcode() const {return this->code;}
    typedef std::vector<std::string> PumpingStationsH;
private:
    int id;
    std::string code;
};

class Edge;
class Vertex;
class Graph;

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double cap, bool direction);

    Vertex * getDest() const;
    double getCapacity() const;
    bool isSelected() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
    double residual;
    friend class Graph;
    friend class Vertex;
protected:
    Vertex *dest; // destination vertex
    double capacity; // edge weight, can also be used for capacity
    bool direction;

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems

};
class Vertex {
public:
    enum class Type { PumpingStations, Reservoir, City };
    explicit Vertex(nodeTID nodeTypeId);

    [[nodiscard]] nodeTID getnodeTypeId() const;
    Edge* addEdge(Vertex *d, int capacity, bool direction);
    std::list<Edge *> getAdj() const;
    bool isVisited() const;
    double getDist() const;
    std::vector<std::string> getPath() const;

    void setVisited(bool visited);
    void setDist(double dist);
    int queueIndex = 0;
    friend class Graph;
protected:
    nodeTID nodeTypeId;
    std::list<Edge* > adj;

    // auxiliary fields
    bool visited = false;
    double dist = 0;
    std::vector<std::string> parents;

    std::vector<Edge *> incoming; // incoming edges

};

/*!
 * @note As the data is organized by id and the code contains the id
 * the string of the code as the node type in the start of the string and the id, separated by '_'
 */

class Graph {
    // vertex set 3 types of nodes,
    //index 0 represents R -> Reservoir
    //index 1 represents Ps -> PumpingStation
    //index 2 represents C -> City
    std::unordered_map<std::string, int> nodes = {{"C", 0}, {"R", 1}, {"PS", 2}};
    std::vector<std::vector<Vertex *>> vertexSet;
public:

    std::tuple<int, int> getNodeTypeId(const std::string &nodeTypeId) const;
    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    Vertex *findVertex(const nodeTID & nodeTypeId) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const nodeTID & nodeTypeId);
    bool removeVertex(const std::string &in);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const std::string &source, const std::string &dest, double capacity, bool direction);
    bool removeEdge(const std::string &source, const std::string &dest);
    bool addBidirectionalEdge(const std::string &source, const std::string &dest, double capacity);

    int getNumVertex() const;
    std::vector<std::vector<Vertex *>> getVertexSet() const;
};

/************************* Vertex  **************************/

Vertex::Vertex(nodeTID nodeTypeId): nodeTypeId(std::move(nodeTypeId)) {}

Edge * Vertex::addEdge(Vertex *d, int capacity, bool direction)
{
    Edge* newEdge = new Edge(this, d, capacity, direction);
    adj.push_back(newEdge);
    return newEdge;
}

nodeTID Vertex::getnodeTypeId() const
{
    return this->nodeTypeId;
}

std::list<Edge*> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

double Vertex::getDist() const {
    return this->dist;
}

std::vector<std::string> Vertex::getPath() const {
    return this->parents;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

/********************** Edge  ****************************/

Edge::Edge(Vertex* orig, Vertex* dest, double capacity, bool direction):
                    orig(orig), dest(dest), capacity(capacity),  direction(direction){}

Vertex* Edge::getDest() const {
    return this->dest;
}

double Edge::getCapacity() const {
    return this->capacity;
}

Vertex* Edge::getOrig() const {
    return this->orig;
}

Edge* Edge::getReverse() const {
    return this->reverse;
}

bool Edge::isSelected() const {
    return this->selected;
}

double Edge::getFlow() const {
    return flow;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}
#endif
