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

/**
 * @brief A class responsible for managing data and performing operations on the water management system.
 */
class DataManager {

public:

    /**
     * @brief Builds a graph representing the water management system.
     *
     * Constructs a graph from the provided data maps of cities, pipes, pumps, and reservoirs.
     *
     * @param citiesMap Map of cities.
     * @param pipesMultiMap Multi-map of pipes.
     * @param pumpsMap Map of pumps.
     * @param reservoirsMap Map of reservoirs.
     * @return The constructed graph.
     */
    static Graph buildGraph(City::CitiesMap citiesMap = City::getCitiesMap(),
                            Pipe::PipesMultiMap pipesMultiMap = Pipe::getPipesMultiMap(),
                            Pump::PumpsMap pumpsMap = Pump::getPumpsMap(),
                            Reservoir::ReservoirsMap reservoirsMap = Reservoir::getReservoirsMap());

    /**
     * @brief Resets the 'Using' status of vertices and edges in the graph.
     *
     * Resets the 'Using' status of all vertices and edges in the graph to 'true'.
     *
     * @param graph The graph to reset.
     */
    static void resetUsing(Graph* graph);


    /**
    * @brief Implements the Edmonds-Karp algorithm for finding maximum flow in a graph.
    *
    * This algorithm finds the maximum flow from a source to a sink in the graph.
    * It uses breadth-first search to find augmenting paths and then augments flow along those paths.
    * @param g The graph.
    * @param source The optional source vertex code. If empty, the super source vertex is used.
    * @param target The optional target vertex code. If empty, the super sink vertex is used.
    * @Complexity O(V * E^2)
    * @Complexity V = number of vertexes
    * @Complexity E = number of edges
    */
    static void edmondsKarp(Graph *g, const std::string& source = "", const std::string& target = "");


private:

    /**
    * @brief Helper function to test and visit vertices during breadth-first search.
    *
    * This function tests if a vertex can be visited during breadth-first search based on the residual capacity of an edge.
    *
    * @param q The queue of vertices to visit.
    * @param e The edge to test.
    * @param w The vertex to visit.
    * @param residual The residual capacity of the edge.
    */
    static void testAndVisit(std::queue<Vertex*> &q, Edge *e, Vertex *w, double residual);

    /**
     * @brief Helper function to find an augmenting path from source to sink.
     *
     * This function finds an augmenting path from source to sink using breadth-first search.
     *
     * @param g The graph.
     * @param s The source vertex.
     * @param t The sink vertex.
     * @return True if an augmenting path is found, false otherwise.
     */
    static bool findAugmentingPath(Graph *g, Vertex *s, Vertex *t);

    /**
     * @brief Helper function to find the minimum residual capacity along an augmenting path.
     *
     * This function finds the minimum residual capacity along an augmenting path.
     *
     * @param s The source vertex.
     * @param t The sink vertex.
     * @return The minimum residual capacity.
     */
    static double findMinResidualAlongPath(Vertex *s, Vertex *t);

    /**
     * @brief Helper function to augment flow along an augmenting path.
     *
     * This function augments flow along an augmenting path in the graph.
     *
     * @param s The source vertex.
     * @param t The sink vertex.
     * @param f The flow to augment.
     */
    static void augmentFlowAlongPath(Vertex *s, Vertex *t, double f);

};


#endif //WATER_MANAGEMENT_DATAMANAGER_H
