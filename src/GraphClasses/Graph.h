#ifndef WATER_MANAGEMENT_GRAPH_H
#define WATER_MANAGEMENT_GRAPH_H

#include <vector>
#include "Vertex.h"

class Edge;
class Vertex;

class Graph {
public:
    Graph();
    ~Graph();

    Vertex* findVertex(const std::string &code) const;
    Vertex* getSuperSource() const;
    Vertex* getSuperSink() const;

    bool addVertex(const std::string &code);
    bool removeVertex(const std::string &code);

    bool addEdge(const std::string &src, const std::string &dest, double w);
    bool removeEdge(const std::string &src, const std::string &dest);
    bool addBidirectionalEdge(const std::string &src, const std::string &dest, double w);

    bool addSource(const std::string &code, double weight);
    bool removeSource(const std::string &code);
    bool addSink(const std::string &code, double weight);
    bool removeSink(const std::string &code);

    int getNumVertex() const;

    std::vector<Vertex*> getVertexSet() const;
    std::vector<Vertex*> getSourceSet() const;
    std::vector<Vertex*> getSinkSet() const;

    bool setVertexUsing(const std::string &code, bool Using);
    bool setEdgeUsing(const std::string &org, const std::string &dest, bool Using, bool bothDirections = 1);


private:

    std::vector<Vertex*> vertexSet;

    std::vector<Vertex*> sourceSet;
    std::vector<Vertex*> sinkSet;

    Vertex* superSource;
    Vertex* superSink;
};


#endif //WATER_MANAGEMENT_GRAPH_H
