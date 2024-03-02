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
#include "Cities.h"
#include "Reservoir.h"

#define nodeinfo std::pair<int, std::string>

class Edge;
class Vertex;
class Graph;

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double cap, bool direction);

    Vertex * getDest() const;
    double getWeight() const;
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

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems

};
class Vertex {
public:
    explicit Vertex(std::string nodeTypeid);

    std::string getnodeTypeId() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    double getDist() const;
    std::vector<int> getPath() const;

    void setVisited(bool visited);
    void setDist(double dist);
    void setPath(Edge *path);
    Edge * addEdge(Vertex *dest, double w);
    friend class Graph;
protected:
    std::string nodeTypeid;
    std::list<Edge > adj;

    // auxiliary fields
    bool visited = false;
    double dist = 0;
    std::vector<int> parents;

    std::vector<Edge *> incoming; // incoming edges

};

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

/*!
 * @note As the data is organized by id and the code contains the id
 * the string of the code as the node type in the start of the string and the id, separated by '_'
 */

class Graph {

    std::vector<Vertex *> vertexSet;    // vertex set
public:

    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    Vertex *findVertex(const std::string &in) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const std::string &in);
    bool removeVertex(const std::string &in);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const std::string &source, const std::string &dest, double w);
    bool removeEdge(const std::string &source, const std::string &dest);
    bool addBidirectionalEdge(const std::string &source, const std::string &dest, double w);

    int getNumVertex() const;
    std::vector<Vertex *> getVertexSet() const;
};
#endif
