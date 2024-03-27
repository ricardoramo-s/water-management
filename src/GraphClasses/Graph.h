#ifndef WATER_MANAGEMENT_GRAPH_H
#define WATER_MANAGEMENT_GRAPH_H


template <class T>
class Graph {
public:
    ~Graph();

    Vertex<T> *findVertex(const T &in) const;

    bool addVertex(const T &in);
    bool removeVertex(const T &in);


    bool addEdge(const T &sourc, const T &dest, double w);
    bool removeEdge(const T &source, const T &dest);
    bool addBidirectionalEdge(const T &sourc, const T &dest, double w);

    int getNumVertex() const;
    std::vector<Vertex<T> *> getVertexSet() const;

    std:: vector<T> dfs() const;
    std:: vector<T> dfs(const T & source) const;
    void dfsVisit(Vertex<T> *v,  std::vector<T> & res) const;
    std::vector<T> bfs(const T & source) const;

    bool isDAG() const;
    bool dfsIsDAG(Vertex<T> *v) const;
    std::vector<T> topsort() const;

private:
    std::vector<Vertex<T>*> vertexSet;    // vertex set

    int findVertexIdx(const T &in) const;
};


#endif //WATER_MANAGEMENT_GRAPH_H
