#include <iostream>
#include "DataManager.h"
using namespace std;

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
                throw std::logic_error("error adding PtP edge");
        } else {
            if (!graph.addBidirectionalEdge(pipe.first.first, pipe.first.second, pipe.second->getCapacity()))
                throw std::logic_error("error adding PtP edge");
        }
    }

    for (auto pipe : pipesMultiMap.getPtCMAP()) {

        if (pipe.second->getDirection()) {
            if (!graph.addEdge(pipe.first.first, pipe.first.second, pipe.second->getCapacity()))
                throw std::logic_error("error adding PtC edge");
        } else {
            if (!graph.addBidirectionalEdge(pipe.first.first, pipe.first.second, pipe.second->getCapacity()))
                throw std::logic_error("error adding PtC edge");
        }
    }

    return graph;

}


void DataManager::testAndVisit(std::queue<Vertex*> &q, Edge *edge, Vertex *w, double residual) {

    if (!w->isVisited() && residual > 0 && w->isUsing()) {
        w->setVisited(true);
        w->setPath(edge);
        q.push(w);
    }
}


bool DataManager::findAugmentingPath(Graph *graph, Vertex *src, Vertex *dest) {

    for(Vertex* vertex : graph->getVertexSet()) {
        vertex->setVisited(false);
    }

    src->setVisited(true);
    std::queue<Vertex *> q;
    q.push(src);

    while(! q.empty() && ! dest->isVisited()) {
        Vertex* vertex = q.front();
        q.pop();
        for (Edge* edge: vertex->getAdj()) {
            if (edge->isUsing())
                testAndVisit(q, edge, edge->getDest(), edge->getWeight() - edge->getFlow());
        }
        for (Edge* edge: vertex->getIncoming()) {
            if (edge->isUsing())
                testAndVisit(q, edge, edge->getOrig(), edge->getFlow());
        }
    }
    return dest->isVisited();
}


double DataManager::findMinResidualAlongPath(Vertex *src, Vertex *dest) {

    double f = INF;

    for (Vertex* vertex = dest; vertex != src;) {

        Edge* edge = vertex->getPath();

        if (edge->getDest() == vertex) {
            f = std::min(f, edge->getWeight() - edge->getFlow());
            vertex = edge->getOrig();
        } else {
            f = std::min(f, edge->getFlow());
            vertex = edge->getDest();
        }
    }

    return f;
}


void DataManager::augmentFlowAlongPath(Vertex *src, Vertex *dest, double f) {

    for (Vertex* vertex = dest; vertex != src; ) {
        Edge* edge = vertex->getPath();
        double flow = edge->getFlow();
        if (edge->getDest() == vertex) {
            edge->setFlow(flow + f);
            vertex = edge->getOrig();
        } else {
            edge->setFlow(flow - f);
            vertex = edge->getDest();
        }
    }
}


void DataManager::edmondsKarp(Graph *graph, const std::string& source, const std::string& target) {

    Vertex* src= nullptr;
    Vertex* dest= nullptr;

    if (source.empty()) src = graph->getSuperSource();
    else src = graph->findVertex(source);

    if (target.empty()) dest= graph->getSuperSink();
    else dest= graph->findVertex(target);


    if (src == nullptr || dest== nullptr || src == dest)
        throw std::logic_error("Invalid source and/or target vertex");

    for (Vertex* vertex : graph->getVertexSet()) {
        for (Edge* edge: vertex->getAdj()) {
            edge->setFlow(0);
        }
    }

    while( findAugmentingPath(graph, src, dest) ) {
        double f = findMinResidualAlongPath(src, dest);
        augmentFlowAlongPath(src, dest, f);
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

double DataManager::getMaxFlow(Graph *graph) {

    double ret = 0;
    for (Edge* edge : graph->getSuperSink()->getIncoming()) ret += edge->getFlow();

    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


double DataManager::getAvgFlow(const double& flow, const std::vector<Edge*>& edgeSet) {
    return flow/edgeSet.size();
}

double DataManager::addAvgToEdges(const double& maxFlow, double& usedFlow, std::vector<Edge*>& edgeSet) {

    int avgFlow = getAvgFlow(maxFlow - usedFlow, edgeSet);

    for (Edge* edge : edgeSet) {

        if (edge->getFlow() + avgFlow > edge->getWeight()) {
            int n = edge->getWeight() - edge->getFlow();
            edge->setFlow(edge->getWeight());
            //usedFlow += n;
        } else {
            edge->setFlow(edge->getFlow() + avgFlow);
            //usedFlow += avgFlow;
        }
    }

    return 0;
}

void DataManager::processVertex(Vertex* vertex, std::set<Vertex*>& processing, std::vector<Edge*>& edgeSet, Graph* graph) {

    int input = 0;
    int output = 0;

    for (Edge* edge : vertex->getIncoming()) {
        input += edge->getFlow();
    }

    for (Edge* edge : vertex->getAdj()) {
        output += edge->getFlow();
    }

    cout << vertex->getCode() << " " << input << " " << output << "\n";

    if (input == output) return;

    if (vertex->getAdj().empty()) return;
    if (vertex->getIncoming().empty()) return;


    while (input > output) {

        int remain = input - output;
        int outN = 0; //number of not full outgoing edges

        for (Edge *edge: vertex->getAdj()) {
            if (edge->getFlow() < edge->getWeight()) {
                edge->setUsing(true);
                outN++;
            } else edge->setUsing(false);
        }

        if (outN == 0 && remain > 0) {

            //remove from input
            while (remain > 0) {
                for (Edge* edge : vertex->getIncoming()) {
                    if (std::find(edgeSet.begin(), edgeSet.end(), edge) == edgeSet.end()) continue;

                    if (remain <= 0) {
                        for (Edge* edge : vertex->getIncoming()) {
                            edgeSet.erase(std::find(edgeSet.begin(), edgeSet.end(), edge));
                        }
                        return;
                    }
                    edge->setFlow(edge->getFlow() - 1);
                    remain--;
                    processing.insert(edge->getOrig());
                }
            }
        }

        int avg = remain / outN;
        if (avg == 0) avg = 1;

        for (Edge *edge: vertex->getAdj()) {
            if (output >= input) break;

            if (!edge->isUsing()) continue;
            int toAdd = std::min(avg, (int) (edge->getWeight() - edge->getFlow()));
            edge->setFlow(edge->getFlow() + toAdd);
            output += toAdd;
            processing.insert(edge->getDest());
        }
    }


    while (output > input) {

        int remain = output - input;
        int inN = 0; //number of not full incoming edges

        for (Edge *edge: vertex->getIncoming()) {

            if (edge->getFlow() < edge->getWeight()) {
                edge->setUsing(true);
                inN++;
            } else edge->setUsing(false);
        }

        if (inN == 0 && remain > 0) {
            //remove from output
            while (remain > 0) {

                for (Edge* edge : vertex->getAdj()) {
                    if (std::find(edgeSet.begin(), edgeSet.end(), edge) == edgeSet.end()) continue;

                    if (remain <= 0) {
                        for (Edge* edge : vertex->getAdj()) {
                            edgeSet.erase(std::find(edgeSet.begin(), edgeSet.end(), edge));
                        }
                        return;
                    }
                    edge->setFlow(edge->getFlow() - 1);
                    remain--;
                    processing.insert(edge->getDest());
                }
            }
        }

        int avg = remain / inN;

        if (avg == 0) avg = 1;

        for (Edge *edge: vertex->getIncoming()) {
            if (input >= output) break;

            if (!edge->isUsing()) continue;
            int toAdd = std::min(avg, (int) (edge->getWeight() - edge->getFlow()));
            edge->setFlow(edge->getFlow() + toAdd);
            input += toAdd;
            processing.insert(edge->getOrig());
        }
    }
}

void DataManager::balanceFlow(Graph* graph, std::vector<Edge*>& edgeSet) {

    std::set<Vertex*> processing;

    for (Vertex* vertex : graph->getVertexSet()) processing.insert(vertex);

    while (!processing.empty()) {
        Vertex* vertex = *processing.begin();
        processing.erase(processing.begin());
        processVertex(vertex, processing, edgeSet, graph);
        for (Edge* edge : edgeSet) edge->setUsing(false);
    }
}

void DataManager::removeFullEdges(std::vector<Edge*>& edgeSet) {

    auto it = edgeSet.begin();

    while (it != edgeSet.end()) {
        if ((*it)->getFlow() == (*it)->getWeight()) it = edgeSet.erase(it);
        else it++;
    }
}

void DataManager::balanceGraph(Graph* graph, int maxFlow) {

    DataManager::resetUsing(graph);

    double usedFlow = 0;
    std::vector<Edge*> edgeSet = graph->getEdgeSet();

    //while (usedFlow < maxFlow - 10) {
    for (int i = 0; i < 1; i++) {

        addAvgToEdges(maxFlow, usedFlow, edgeSet);
        balanceFlow(graph, edgeSet);
        removeFullEdges(edgeSet);

    }

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

