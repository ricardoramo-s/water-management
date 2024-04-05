#ifndef WATER_MANAGEMENT_DATAMANAGER_H
#define WATER_MANAGEMENT_DATAMANAGER_H

#include <stdexcept>
#include <limits>
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

    static void edmondsKarp(Graph *g, std::string source, std::string target);

private:

    static void testAndVisit(std::queue<Vertex*> &q, Edge *e, Vertex *w, double residual);
    static bool findAugmentingPath(Graph *g, Vertex *s, Vertex *t);
    static double findMinResidualAlongPath(Vertex *s, Vertex *t);
    static void augmentFlowAlongPath(Vertex *s, Vertex *t, double f);

};


#endif //WATER_MANAGEMENT_DATAMANAGER_H
