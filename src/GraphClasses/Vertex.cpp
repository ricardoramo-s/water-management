#include "Vertex.h"


Vertex::Vertex(std::string code) {
    this->code = std::move(code);
}

Vertex::~Vertex() {
    this->removeIncomingEdges();
    this->removeOutgoingEdges();
}


Edge* Vertex::addEdge(Vertex *dest, double w) {

    Edge* edge = new Edge(this, dest, w);
    adj.push_back(edge);
    dest->incoming.push_back(edge);
    return edge;
}

bool Vertex::removeEdge(Vertex* dest) {

    for (Edge* edge : adj) {
        if (edge->getDest() == dest) {
            deleteEdge(edge);
            return true;
        }
    }

    return false;
}

void Vertex::removeOutgoingEdges() {

    auto it = adj.begin();

    while (it != adj.end()) {
        deleteEdge(*it);
        it++;
    }
}

void Vertex::removeIncomingEdges() {

    auto it = incoming.begin();

    while (it != incoming.end()) {
        deleteEdge(*it);
        it++;
    }
}


std::vector<Edge*> Vertex::getAdj() const {
    return adj;
}

std::vector<Edge*> Vertex::getIncoming() const {
    return incoming;
}


double Vertex::getDist() const {
    return dist;
}

Edge* Vertex::getPath() const {
    return path;
}


void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}


std::string Vertex::getCode() const {
    return code;
}

bool Vertex::isVisited() const {
    return visited;
}

bool Vertex::isProcessing() const {
    return processing;
}


void Vertex::setCode(std::string code) {
    this->code = code;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setProcessing(bool processing) {
    this->processing = processing;
}

//TODO
void Vertex::setIndegree(unsigned int indegree) {

}

//TODO
unsigned int Vertex::getIndegree() const {
    return 0;
}


void Vertex::deleteEdge(Edge *edge) {

    Vertex* orig = edge->getOrig();
    Vertex* dest = edge->getDest();

    auto it = std::find(orig->getAdj().begin(), orig->getAdj().end(), edge);
    orig->getAdj().erase(it);

    it = std::find(dest->getIncoming().begin(), dest->getIncoming().end(), edge);
    dest->getIncoming().erase(it);

    delete edge;
}


