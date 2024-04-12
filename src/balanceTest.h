#ifndef WATER_MANAGEMENT_BALANCETEST_H
#define WATER_MANAGEMENT_BALANCETEST_H

#include <unordered_set>
#include "DataManagement/DataReader.h"
#include "DataManagement/DataManager.h"

using namespace std;


/*
struct edgeHash {
    size_t operator()(const Edge* obj) const {
        size_t hash1 = hash<string>{}(obj->getOrig()->getCode());
        size_t hash2 = hash<string>{}(obj->getDest()->getCode());
        return hash1 ^ (hash2 << 8);
    }
};

struct vertexHash {
    size_t operator()(const Vertex* obj) const {
        size_t hash1 = hash<string>{}(obj->getCode());
        return hash1;
    }
};

typedef unordered_set<Vertex*, vertexHash> Visited;



double sumFlow(const vector<Edge*>& edgeVector) {
    double sum = 0;
    for (Edge* edge : edgeVector) sum += edge->getFlow();
    return sum;
}

void dfsBalance(Vertex* vertex, Visited visited) {

    visited.insert(vertex);

    for (Edge)

}


void balanceGraph(Graph* graph) {

    Vertex* vertex = graph->getSuperSource();
    Visited visited;

}
 */

double getMaxFlow(Graph* graph);

string printEdge(Edge *edge) {

    string ret;
    ret += edge->getOrig()->getCode() + "->" + edge->getDest()->getCode() + "(" + to_string((int) edge->getFlow())
           + "|" + to_string((int) edge->getWeight()) + ")";
    return ret;
}

void printEdges(Graph *graph) {

    vector<Edge *> vec = graph->getEdgeSet();

    std::sort(vec.begin(), vec.end(), [](const Edge *edge1, const Edge *edge2) {
        //return edge1->getOrig()->getCode() < edge2->getOrig()->getCode();
        //return edge2->getWeight() - edge2->getFlow() < edge1->getWeight() - edge1->getFlow();
        return edge1->getFlow() > edge2->getFlow();
    });

    for (auto edge: vec) {
        cout << printEdge(edge) << "\n";
    }
    cout << ":::" << getMaxFlow(graph);

    cout << "\n/////////////////////////////////\n";
}

void printGraphVertexEdges(Graph* graph) {

    for (auto vertex : graph->getVertexSet()) {

        cout << "--- " << vertex->getCode() << " ---\n";

        cout << "|||IN:||||\n";

        for (auto edge : vertex->getIncoming()) {
            cout << printEdge(edge) << "\n";
        }

        cout << "\n|||Out:|||\n";

        for (auto edge : vertex->getAdj()) {
            cout << printEdge(edge) << "\n";
        }

        cout << "\n\n";
    }
}

void testAndVisit(std::queue<Vertex*> &q, Edge *edge, Vertex *vertex, double residual) {

    if (!vertex->isVisited() && residual > 0 && vertex->isUsing()) {
        vertex->setVisited(true);
        vertex->setPath(edge);
        q.push(vertex);
    }
}


bool findAugmentingPath(Graph *graph, Vertex *src, Vertex *dest) {

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
                testAndVisit(q, edge, edge->getDest(), edge->getTWeight() - edge->getFlow());
        }
        for (Edge* edge: vertex->getIncoming()) {
            if (edge->isUsing())
                testAndVisit(q, edge, edge->getOrig(), edge->getFlow());
        }
    }
    return dest->isVisited();
}


double findMinResidualAlongPath(Vertex *src, Vertex *dest) {

    double f = INF;

    for (Vertex* vertex = dest; vertex != src;) {

        Edge* edge = vertex->getPath();

        if (edge->getDest() == vertex) {
            f = std::min(f, edge->getTWeight() - edge->getFlow());
            vertex = edge->getOrig();
        } else {
            f = std::min(f, edge->getFlow());
            vertex = edge->getDest();
        }
    }

    return f;
}


void augmentFlowAlongPath(Vertex *src, Vertex *dest, double f) {

    for (Vertex* vertex = dest; vertex != src; ) {
        Edge* edge = vertex->getPath();

        edge->setUsing(false);

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


bool edmondsKarp(Graph *graph, const std::string& source = "", const std::string& target = "") {

    Vertex* src= nullptr;
    Vertex* dest= nullptr;

    bool alterationMade = false;

    if (source.empty()) src = graph->getSuperSource();
    else src = graph->findVertex(source);

    if (target.empty()) dest= graph->getSuperSink();
    else dest= graph->findVertex(target);

    if (src == nullptr || dest== nullptr || src == dest)
        throw std::logic_error("Invalid source and/or target vertex");

    while(findAugmentingPath(graph, src, dest) ) {
        alterationMade = true;
        double f = findMinResidualAlongPath(src, dest);
        augmentFlowAlongPath(src, dest, f);
    }

    return alterationMade;
}


int exploreIndegree(Graph* graph) {

    queue<pair<Vertex*, int>> q;
    pair<Vertex*, int> v;
    q.emplace(graph->getSuperSource(), 0);
    int max = 0;

    for (Vertex* vertex : graph->getVertexSet()) vertex->setVisited(false);

    while (!q.empty()) {
        v = q.front();
        v.first->setIndegree(v.second);
        if (v.second > max && v.first != graph->getSuperSink()) max = v.second;
        q.pop();

        for (Edge* edge : v.first->getAdj()) {
            if (!edge->getDest()->isVisited()) {
                q.emplace(edge->getDest(), v.second+1);
                edge->getDest()->setVisited(true);
            }
        }
    }

    return max;
}

typedef unordered_map<int, vector<Edge*>> IndegreeEdges;

IndegreeEdges getEdgesByIndegree(Graph* graph, int max) {

    IndegreeEdges indegreeEdges;

    vector<Edge*> v;

    for (int i = 0; i <= max; i++) indegreeEdges.emplace(i,v);

    for (Edge* edge : graph->getSuperSource()->getAdj()) {
        indegreeEdges[0].push_back(edge);
    }

    for (Edge* edge : graph->getSuperSink()->getIncoming()) {
        indegreeEdges[0].push_back(edge);
    }

    for (Vertex* vertex : graph->getVertexSet()) {
        if (vertex == graph->getSuperSink() || vertex == graph->getSuperSink()) continue;
        for (Edge* edge : vertex->getAdj()) {
            if (edge->getDest() == graph->getSuperSink()) continue;
            indegreeEdges[vertex->getIndegree()].push_back(edge);
        }
    }

    return indegreeEdges;
}

double getMaxFlow(Graph* graph) {
    double max = 0;
    for (Edge* edge : graph->getSuperSink()->getIncoming()) max += edge->getFlow();
    return max;
}

void setTWeight(Graph* graph, double tWeight) {
    for (Edge* edge : graph->getEdgeSet()) edge->setTWeight(min(tWeight, edge->getWeight()));
}

void augmentTWeight(const vector<Edge*>& edgeVector, double tWeight) {
    for (Edge* edge : edgeVector) edge->setTWeight(min(edge->getTWeight() + tWeight, edge->getWeight()));
}

void removeEdges(const vector<Edge*>& edgeVector, double med) {
    for (Edge* edge : edgeVector) {
        if (!edge->isUsing()) continue;
        if (edge->getFlow() < med) edge->setUsing(false);
    }
}

void resetUsing(const vector<Edge*>& edgeVector) {
    for (Edge* edge : edgeVector) edge->setUsing(true);
}

double notUsingProportion(const vector<Edge*>& edgeVector) {
    int count = 0;
    for (Edge* edge : edgeVector) {
        if (!edge->isUsing()) count++;
    }
    return (double) count / (double) edgeVector.size();
}

double getEdgesNumber(const vector<Edge*>& edgeVector) {
    double count = 0;
    for (Edge* edge : edgeVector) {
        if (edge->isUsing()) count++;
    }
    return count;
}

vector<Edge*> findMostNotUsingVector(const IndegreeEdges& indegreeEdges) {
    double max = 0;
    vector<Edge*> ret;

    for (const auto& n : indegreeEdges) {
        double p = notUsingProportion(n.second);
        if (p > max) {
            ret = n.second;
            max = p;
        }
    }
    return ret;
}

void balanceGraph(Graph* graph) {

    const double maxFlow = getMaxFlow(graph);
    double currentFlow = 0;
    double nEdges = getEdgesNumber(graph->getEdgeSet());

    int maxIndegree = exploreIndegree(graph);
    IndegreeEdges indegreeEdges = getEdgesByIndegree(graph, maxIndegree);

    double med = maxFlow / nEdges;

    for (Edge* edge : graph->getEdgeSet()) edge->setFlow(0);
    for (Edge* edge : graph->getEdgeSet()) edge->setUsing(true);

    setTWeight(graph, med);


    while (maxFlow - currentFlow > 10) {


        if (!edmondsKarp(graph)) {
            vector<Edge *> lessUsed = findMostNotUsingVector(indegreeEdges);
            resetUsing(lessUsed);
            augmentTWeight(lessUsed, med);
        }

        currentFlow = getMaxFlow(graph);
    }

    edmondsKarp(graph);
}


#endif //WATER_MANAGEMENT_BALANCETEST_H
