#ifndef WATER_MANAGEMENT_GRAPH_H
#define WATER_MANAGEMENT_GRAPH_H

#include <vector>
#include "Vertex.h"

class Edge;
class Vertex;

class Graph {
public:

    /**
      * @brief Constructor.
      */
    Graph();

    /**
     * @brief Destructor.
     */
    ~Graph();

    /**
     * @brief Finds a vertex in the graph based on its code.
     *
     * @param code The code of the vertex to find.
     * @return Pointer to the found vertex, or nullptr if not found.
     * @complexity O(n)
     * @complexity n = vertexSet size
     */
    Vertex* findVertex(const std::string &code) const;

    /**
     * @brief Gets the super source vertex of the graph.
     *
     * @return Pointer to the super source vertex.
     */
    Vertex* getSuperSource() const;

    /**
     * @brief Gets the super sink vertex of the graph.
     *
     * @return Pointer to the super sink vertex.
     */
    Vertex* getSuperSink() const;

    /**
     * @brief Adds a vertex to the graph.
     *
     * @param code The code of the vertex to add.
     * @return True if the vertex was added successfully, false otherwise.
     * @complexity O(n)
     * @complexity n = vertexSet size
     */
    bool addVertex(const std::string &code);

    /**
     * @brief not implemented
     */
    bool removeVertex(const std::string &code);

    /**
     * @brief Adds an edge between two vertices in the graph.
     *
     * @param src The code of the source vertex.
     * @param dest The code of the destination vertex.
     * @param w The weight of the edge.
     * @return True if the edge was added successfully, false otherwise.
     * @complexity O(n)
     * @complexity n = vertexSet size
     */
    bool addEdge(const std::string &src, const std::string &dest, double w);

    /**
     * @brief not implemented
     */
    bool removeEdge(const std::string &src, const std::string &dest);

    /**
     * @brief Adds a bidirectional edge between two vertices in the graph.
     *
     * @param src The code of the source vertex.
     * @param dest The code of the destination vertex.
     * @param w The weight of the edge.
     * @return True if the bidirectional edge was added successfully, false otherwise.
     * @complexity O(n)
     * @complexity n = vertexSet size
     */
    bool addBidirectionalEdge(const std::string &src, const std::string &dest, double w);

    /**
     * @brief Adds a source vertex to the graph with the given weight.
     *
     * @param code The code of the source vertex to add.
     * @param weight The weight of the source vertex.
     * @return True if the source vertex was added successfully, false otherwise.
     * @complexity O(n)
     * @complexity n = vertexSet size
     */
    bool addSource(const std::string &code, double weight);

    /**
     * @brief not implemented
     */
    bool removeSource(const std::string &code);

    /**
     * @brief Adds a sink vertex to the graph with the given weight.
     *
     * @param code The code of the sink vertex to add.
     * @param weight The weight of the sink vertex.
     * @return True if the sink vertex was added successfully, false otherwise.
     * @complexity O(n)
     * @complexity n = vertexSet size
     */
    bool addSink(const std::string &code, double weight);

    /**
     * @brief not implemented
     */
    bool removeSink(const std::string &code);

    /**
     * @brief Gets the number of vertices in the graph.
     *
     * @return The number of vertices in the graph.
     * @complexity O(n)
     * n = vertexSet size
     */
    int getNumVertex() const;

    /**
     * @brief Gets the set of vertices in the graph.
     *
     * @return Vector containing pointers to all vertices in the graph.
     */
    std::vector<Vertex*> getVertexSet() const;

    /**
     * @brief Gets the set of source vertices in the graph.
     *
     * @return Vector containing pointers to all source vertices in the graph.
     */
    std::vector<Vertex*> getSourceSet() const;

    /**
     * @brief Gets the set of sink vertices in the graph.
     *
     * @return Vector containing pointers to all sink vertices in the graph.
     */
    std::vector<Vertex*> getSinkSet() const;

    /**
     * @brief Sets the 'Using' flag of a vertex in the graph.
     *
     * @param code The code of the vertex to set the flag for.
     * @param Using The value to set the flag to.
     * @return True if the flag was set successfully, false otherwise.
     * @complexity O(n)
     * n = vertexSet size
     */
    bool setVertexUsing(const std::string &code, bool Using);

    /**
     * @brief Sets the 'Using' flag of an edge in the graph.
     *
     * @param org The code of the source vertex of the edge.
     * @param dest The code of the destination vertex of the edge.
     * @param Using The value to set the flag to.
     * @param bothDirections If true, sets the flag for both directions of the edge.
     * @return True if the flag was set successfully, false otherwise.
     * @complexity O(2*n1 + n2)
     * @complexity n1 = edgeSet size
     * @complexity n2 = org.adj size
     */
    bool setEdgeUsing(const std::string &org, const std::string &dest, bool Using, bool bothDirections = true);


private:

    /**
     * @brief Vector containing pointers to all vertices in the graph.
     */
    std::vector<Vertex*> vertexSet;

    /**
     * @brief Vector containing pointers to all source vertices in the graph.
     */
    std::vector<Vertex*> sourceSet;

    /**
     * @brief Vector containing pointers to all sink vertices in the graph.
     */
    std::vector<Vertex*> sinkSet;

    /**
     * @brief Pointer to the super source vertex of the graph.
     */
    Vertex* superSource;

    /**
     * @brief Pointer to the super sink vertex of the graph.
     */
    Vertex* superSink;
};


#endif //WATER_MANAGEMENT_GRAPH_H
