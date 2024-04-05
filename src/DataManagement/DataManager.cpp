#include "DataManager.h"



Graph DataManager::buildGraph(City::CitiesMap citiesMap, Pipe::PipesMultiMap pipesMultiMap, Pump::PumpsMap pumpsMap,
                              Reservoir::ReservoirsMap reservoirsMap) {

    Graph graph = Graph();

    for (auto reservoir : reservoirsMap) {
        if (!graph.addSource(reservoir.second->getCode(), reservoir.second->getMaxDelivery()))
            throw std::logic_error("error adding source vertex");
    }

    for (auto pump : pumpsMap) {
        if (!graph.addVertex(pump.second->getCode())) throw std::logic_error("error adding vertex");
    }

    for (auto city : citiesMap) {
        if (!graph.addSink(city.second->getCode(), city.second->getDemand()))
            throw std::logic_error("error adding sink vertex");
    }

    for (auto pipe : pipesMultiMap.getRtPMAP()) {

        if (pipe.second->getDirection()) {
            if (!graph.addEdge(pipe.first.first, pipe.first.second, pipe.second->getCapacity()))
                throw std::logic_error("error adding RtP edge");
        } else {
            if (!graph.addBidirectionalEdge(pipe.first.first, pipe.first.second, pipe.second->getCapacity()))
                throw std::logic_error("error adding RtP edge");
        }
    }

    for (auto pipe : pipesMultiMap.getPtPMAP()) {

        if (pipe.second->getDirection()) {
            if (!graph.addEdge(pipe.first.first, pipe.first.second, pipe.second->getCapacity()))
                throw std::logic_error("error adding RtP edge");
        } else {
            if (!graph.addBidirectionalEdge(pipe.first.first, pipe.first.second, pipe.second->getCapacity()))
                throw std::logic_error("error adding RtP edge");
        }
    }

    for (auto pipe : pipesMultiMap.getPtCMAP()) {

        if (pipe.second->getDirection()) {
            if (!graph.addEdge(pipe.first.first, pipe.first.second, pipe.second->getCapacity()))
                throw std::logic_error("error adding RtP edge");
        } else {
            if (!graph.addBidirectionalEdge(pipe.first.first, pipe.first.second, pipe.second->getCapacity()))
                throw std::logic_error("error adding RtP edge");
        }
    }

    return graph;

}



void DataManager::testAndVisit(std::queue<Vertex*> &q, Edge *e, Vertex *w, double residual) {

    if (!w->isVisited() && residual > 0 && w->isUsing()) {
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}


bool DataManager::findAugmentingPath(Graph *g, Vertex *s, Vertex *t) {

    for(auto v : g->getVertexSet()) {
        v->setVisited(false);
    }

    s->setVisited(true);
    std::queue<Vertex *> q;
    q.push(s);

    while(! q.empty() && ! t->isVisited()) {
        auto v = q.front();
        q.pop();
        for (auto e: v->getAdj()) {
            if (e->isUsing())
                testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
        for (auto e: v->getIncoming()) {
            if (e->isUsing())
                testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
    return t->isVisited();
}

double DataManager::findMinResidualAlongPath(Vertex *s, Vertex *t) {

    double f = INF;

    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
    return f;
}


void DataManager::augmentFlowAlongPath(Vertex *s, Vertex *t, double f) {

    for (auto v = t; v != s; ) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}


void DataManager::edmondsKarp(Graph *g, const std::string& source, const std::string& target) {

    Vertex *s = nullptr;
    Vertex* t = nullptr;

    if (source.empty()) s = g->getSuperSource();
    else s = g->findVertex(source);

    if (target.empty()) t = g->getSuperSink();
    else t = g->findVertex(target);


    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");
    for (auto v : g->getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
    while( findAugmentingPath(g, s, t) ) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
}

void DataManager::resetUsing(Graph *graph) {

    for (Vertex* vertex : graph->getVertexSet()) {
        graph->setVertexUsing(vertex->getCode(), true);

        for (Edge* edge : vertex->getAdj()) {
            graph->setEdgeUsing(vertex->getCode(), edge->getDest()->getCode(), true, false);
        }
    }
}
