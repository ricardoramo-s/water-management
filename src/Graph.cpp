#include "Graph.h"

int Graph::getNumVertex() const
{
    return (int)vertexSet.size();
}

std::vector<std::vector<Vertex *>> Graph::getVertexSet() const
{
    return vertexSet;
}

std::tuple<int, int> Graph::getNodeTypeId(const std::string & nodeTypeId) const
{
    int _ = (int)nodeTypeId.find('_');
    return {nodes.at(nodeTypeId.substr(0, _)),
            atoi(nodeTypeId.substr(_, nodeTypeId.size()).c_str())};
}
/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(const nodeTID &nodeTypeid) const
{
    auto [type, id] = nodeTypeid;
    return vertexSet[nodes.at(type)][id];
}


//TODO add diferent types of nodes

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getInfo() == in) {
            auto v = *it;
            v->removeOutgoingEdges();
            for (auto u : vertexSet) {
                u->removeEdge(v->getInfo());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

bool Graph::addBidirectionalEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void Graph::addReservoir(const std::tuple<const std::string, const int> &nodeTypeId, Reservoir r)
{
    auto [type, id] = nodeTypeId;
    auto *v = new Vertex(nodeTypeId);
    v->setReservoir(std::move(r));
    vertexSet[nodes.at(type)].push_back(v);
}

void Graph::addCity(const std::tuple<const std::string, const int> &nodeTypeId, City c)
{
    auto [type, id] = nodeTypeId;
    auto *v = new Vertex(nodeTypeId);
    v->setReservoir(std::move(r));
    vertexSet[nodes.at(type)].push_back(v);
}

void Graph::addPumpinStation(const std::tuple<const std::string, const int> &nodeTypeId, PumpingStations ps)
{
    auto [type, id] = nodeTypeId;
    auto *v = new Vertex(nodeTypeId);
    v->setReservoir(std::move(r));
    vertexSet[nodes.at(type)].push_back(v);
}

void Graph::removeReservoir(const std::tuple<const std::string, const int> &nodeTypeId, Reservoir r) {

}

void Graph::removeCity(const std::tuple<const std::string, const int> &nodeTypeId, City c) {

}

void Graph::removePumpinStation(const std::tuple<const std::string, const int> &nodeTypeId, PumpingStations ps) {

}
