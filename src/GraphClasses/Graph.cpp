#include "Graph.h"

Graph::Graph() {

    addVertex("super_source");
    addVertex("super_sink");

    superSource = findVertex("super_source");
    superSink = findVertex("super_sink");
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

    Edge* edge = vertex1->addEdge(vertex2, w);

    edgeSet.push_back(edge);

    return true;
}

bool Graph::removeEdge(const std::string &src, const std::string &dest) {

    Vertex* vertex1 = findVertex(src);
    Vertex* vertex2 = findVertex(dest);

    if ((vertex1 == nullptr) || (vertex2 == nullptr)) return false;

    for (auto it = edgeSet.begin(); it != edgeSet.end(); it++) {
        if ((*it)->getOrig()->getCode() == src && (*it)->getDest()->getCode() == dest) {
            edgeSet.erase(it);
        }

    }

    if (!vertex1->removeEdge(vertex2)) return false;

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

    edgeSet.push_back(edge1);
    edgeSet.push_back(edge2);

    return true;
}


bool Graph::addSource(const std::string &code, double weight) {

    if (!addVertex(code)) return false;

    Vertex* vertex = findVertex(code);
    sourceSet.push_back(vertex);

    if (!addEdge("super_source", code, weight)) return false;

    return true;
}

bool Graph::removeSource(const std::string &code) {

    Vertex* vertex = findVertex(code);
    if (!removeVertex(code)) return false;

    auto it = std::find(sourceSet.begin(), sourceSet.end(), vertex);
    sourceSet.erase(it);

    return true;
}

bool Graph::addSink(const std::string &code, double weight) {

    if (!addVertex(code)) return false;

    Vertex* vertex = findVertex(code);
    sinkSet.push_back(vertex);

    if (!addEdge(code, superSink->getCode(), weight)) return false;

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

std::vector<Vertex *> Graph::getSourceSet() const {
    return sourceSet;
}

std::vector<Vertex *> Graph::getSinkSet() const {
    return sinkSet;
}

bool Graph::setVertexUsing(const std::string &code, bool Using) {

    Vertex* vertex = findVertex(code);
    if (vertex == nullptr) return false;

    vertex->setUsing(Using);
    return true;
}

bool Graph::setEdgeUsing(const std::string &org, const std::string &dest, bool Using, bool bothDirections) {

    Vertex* src = findVertex(org);
    Vertex* trg = findVertex(dest);
    if (src == nullptr || trg == nullptr) return false;

    for (Edge* edge : src->getAdj()) {
        if (edge->getDest() == trg) {
            edge->setUsing(Using);
            if (bothDirections) {
                if (edge->getReverse() != nullptr) {
                    edge->getReverse()->setUsing(Using);
                }
            }
            return true;
        }
    }

    return false;
}

std::vector<Edge*> Graph::getEdgeSet() const {
    return edgeSet;
}

