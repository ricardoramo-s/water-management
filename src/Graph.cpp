#include "Graph.h"

#include <utility>

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


//TODO remove Edge & vertex

bool Graph::addEdge(const nodeTID &sourc, const nodeTID &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

bool Graph::addBidirectionalEdge(const nodeTID &sourc, const nodeTID &dest, double capacity) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, capacity);
    auto e2 = v2->addEdge(v1, capacity);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void Graph::addReservoir(const nodeTID &nodeTypeId, Reservoir r)
{
    auto [type, id] = nodeTypeId;
    auto *v = new Vertex(nodeTypeId);
    v->setReservoir(std::move(r));
    vertexSet[nodes.at(type)].push_back(v);
}

void Graph::addCity(const nodeTID &nodeTypeId, City c)
{
    auto [type, id] = nodeTypeId;
    auto *v = new Vertex(nodeTypeId);
    v->setCity(std::move(c));
    vertexSet[nodes.at(type)].push_back(v);
}

void Graph::addPumpingStation(const nodeTID &nodeTypeId, PumpingStations ps)
{
    auto [type, id] = nodeTypeId;
    auto *v = new Vertex(nodeTypeId);
    v->setPStation(std::move(ps));
    vertexSet[nodes.at(type)].push_back(v);
}

void Graph::removeReservoir(const nodeTID &nodeTypeId, Reservoir r)
{

}

void Graph::removeCity(const nodeTID &nodeTypeId, City c)
{

}

void Graph::removePumpingStation(const nodeTID &nodeTypeId, PumpingStations ps)
{

}
