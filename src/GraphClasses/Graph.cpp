#include "Graph.h"

Graph::Graph() {

}

Graph::~Graph() {

}

Vertex* Graph::findVertex(const std::string &code) const {

    for (Vertex* vertex : vertexSet) {
        if (vertex->getCode() == code) return vertex;
    }

    return nullptr;
}

Vertex* Graph::getSuperSource() const {
    return superSource;
}

Vertex* Graph::getSuperSink() const {
    return superSink;
}

bool Graph::addVertex(const std::string &code) {

    for (Vertex* vertex : vertexSet) {
        if (vertex->getCode() == code) return false;
    }

    auto* vertex = new Vertex(code);
    vertexSet.push_back(vertex);

    return true;
}

bool Graph::removeVertex(const std::string &code) {

    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {

        if ((*it)->getCode() == code) {
            delete *it;
            vertexSet.erase(it);
            return true;
        }
    }

    return false;
}

bool Graph::addEdge(const std::string &src, const std::string &dest, double w) {

    Vertex* vertex1 = findVertex(src);
    Vertex* vertex2 = findVertex(dest);

    if ((vertex1 == nullptr) || (vertex2 == nullptr)) return false;

    vertex1->addEdge(vertex2, w);

    return true;
}

bool Graph::removeEdge(const std::string &src, const std::string &dest) {

    Vertex* vertex1 = findVertex(src);
    Vertex* vertex2 = findVertex(dest);

    if ((vertex1 == nullptr) || (vertex2 == nullptr)) return false;

    vertex1->removeEdge(vertex2);

    return true;
}

bool Graph::addBidirectionalEdge(const std::string &src, const std::string &dest, double w) {

    Vertex* vertex1 = findVertex(src);
    Vertex* vertex2 = findVertex(dest);

    if ((vertex1 == nullptr) || (vertex2 == nullptr)) return false;

    Edge *edge1 = vertex1->addEdge(vertex2, w);
    Edge *edge2 = vertex2->addEdge(vertex1, w);

    edge1->setReverse(edge2);
    edge2->setReverse(edge1);

    return true;
}

bool Graph::addSource(const std::string &code) {

    if (!addVertex(code)) return false;

    Vertex* vertex = findVertex(code);
    sourceSet.push_back(vertex);

    return true;
}

bool Graph::removeSource(const std::string &code) {

    Vertex* vertex = findVertex(code);
    if (!removeVertex(code)) return false;

    auto it = std::find(sourceSet.begin(), sourceSet.end(), vertex);
    sourceSet.erase(it);

    return true;
}

bool Graph::addSink(const std::string &code) {

    if (!addVertex(code)) return false;

    Vertex* vertex = findVertex(code);
    sinkSet.push_back(vertex);

    return true;
}

bool Graph::removeSink(const std::string &code) {

    Vertex* vertex = findVertex(code);
    if (!removeVertex(code)) return false;

    auto it = std::find(sinkSet.begin(), sinkSet.end(), vertex);
    sinkSet.erase(it);

    return true;
}

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

