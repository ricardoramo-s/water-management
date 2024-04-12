#ifndef WATER_MANAGEMENT_DATAMANAGER_H
#define WATER_MANAGEMENT_DATAMANAGER_H

#include <stdexcept>
#include <limits>
#include <set>
#include <queue>
#include "../GraphClasses/Graph.h"
#include "../BaseClasses/City.h"
#include "../BaseClasses/Pipe.h"
#include "../BaseClasses/Pump.h"
#include "../BaseClasses/Reservoir.h"

#define INF std::numeric_limits<double>::infinity();


class DataManager {

public:

    static Graph buildGraph(City::CitiesMap citiesMap = City::getCitiesMap(),
                            Pipe::PipesMultiMap pipesMultiMap = Pipe::getPipesMultiMap(),
                            Pump::PumpsMap pumpsMap = Pump::getPumpsMap(),
                            Reservoir::ReservoirsMap reservoirsMap = Reservoir::getReservoirsMap());

    static void resetUsing(Graph* graph);

    static void edmondsKarp(Graph *g, const std::string& source = "", const std::string& target = "");

    static double getMaxFlow(Graph *g);

    static void balanceGraph(Graph* graph, int); //not working


private:

    static void testAndVisit(std::queue<Vertex*> &q, Edge *e, Vertex *w, double residual);
    static bool findAugmentingPath(Graph *g, Vertex *s, Vertex *t);
    static void augmentFlowAlongPath(Vertex *s, Vertex *t, double f);
    static double findMinResidualAlongPath(Vertex *s, Vertex *t);

    ///not working///
    static double getAvgFlow(const double& flow, const std::vector<Edge*>& edgeSet);
    static double addAvgToEdges(const double& maxFlow, double& usedFlow, std::vector<Edge*>& edgeSet);
    static void removeFullEdges(std::vector<Edge*>& edgeSet);
    static void balanceFlow(Graph* graph, std::vector<Edge*>& edgeSet);
    static void processVertex(Vertex* vertex, std::set<Vertex*>& processing, std::vector<Edge*>& edgeSet, Graph* graph);
    /////////////////

};


#endif //WATER_MANAGEMENT_DATAMANAGER_H

