#ifndef WATER_MANAGEMENT_VERTEX_H
#define WATER_MANAGEMENT_VERTEX_H

#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include "Edge.h"

class Edge;

class Vertex {
public:

    explicit Vertex(std::string code);
    ~Vertex();

    Edge* addEdge(Vertex* dest, double w);
    bool removeEdge(Vertex* dest);
    void removeOutgoingEdges();
    void removeIncomingEdges();

    std::vector<Edge*> getAdj() const;
    std::vector<Edge*> getIncoming() const;

    double getDist() const;
    Edge* getPath() const;
    void setDist(double dist);
    void setPath(Edge* path);

    std::string getCode() const;
    bool isVisited() const;
    bool isProcessing() const;
    void setCode(std::string code);
    void setVisited(bool visited);
    void setProcessing(bool processing);

    void setIndegree(unsigned int indegree);
    unsigned int getIndegree() const;

protected:

    void deleteEdge(Edge* edge);

    std::string code;
    std::vector<Edge*> adj;
    std::vector<Edge*> incoming;
    Edge* path = nullptr;

    bool visited = false;
    bool processing = false;
    unsigned int indegree = NULL;
    double dist = NULL;

};


#endif //WATER_MANAGEMENT_VERTEX_H
