//
// Created by bruno on 22/03/2024.
//

#ifndef WATER_MANAGEMENT_VERTEX_H
#define WATER_MANAGEMENT_VERTEX_H

#include <vector>

template <class T>
class Vertex {
public:
    Vertex(T in);

    T getInfo() const;
    std::vector<Edge<T> *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge<T> *getPath() const;
    std::vector<Edge<T> *> getIncoming() const;

    void setInfo(T info);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge<T> *path);
    Edge<T> * addEdge(Vertex<T> *dest, double w);
    bool removeEdge(T in);
    void removeOutgoingEdges();


protected:


    T info;
    std::vector<Edge<T> *> adj;


    bool visited = false;
    bool processing = false;
    unsigned int indegree;
    double dist = 0;
    Edge<T> *path = nullptr;

    std::vector<Edge<T> *> incoming;

    void deleteEdge(Edge<T> *edge);
};


#endif //WATER_MANAGEMENT_VERTEX_H
