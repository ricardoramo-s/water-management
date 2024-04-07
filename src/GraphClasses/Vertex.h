#ifndef WATER_MANAGEMENT_VERTEX_H
#define WATER_MANAGEMENT_VERTEX_H

#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include "Edge.h"

class Edge;

class Vertex {
public:

/**
     * @brief Constructor with parameter.
     *
     * @param code The code of the vertex.
     */
    explicit Vertex(std::string code);

    /**
     * @brief Destructor.
     */
    ~Vertex();

    /**
     * @brief Adds an edge from this vertex to the destination vertex with the given weight.
     *
     * @param dest Pointer to the destination vertex.
     * @param w The weight of the edge.
     * @return Pointer to the created edge.
     * @complexity O(1)
     */
    Edge* addEdge(Vertex* dest, double w);

    /**
     * @brief Removes the edge from this vertex to the given destination vertex.
     *
     * @param dest Pointer to the destination vertex.
     * @return True if the edge was successfully removed, false otherwise.
     * @complexity O((2*n1 + n2))
     * @complexity n1 = adj size
     * @complexity n2 = incoming size
     */
    bool removeEdge(Vertex* dest);

    /**
     * @brief Removes all outgoing edges from this vertex.
     * @complexity O(n1*n2)
     * @complexity n1 = adj size
     * @complexity n2 = incoming average size
     */
    void removeOutgoingEdges();

    /**
     * @brief Removes all incoming edges to this vertex.
     * @complexity O(n1*n2)
     * @complexity n1 = incoming size
     * @complexity n2 = adj average size
     */
    void removeIncomingEdges();

    /**
     * @brief Gets the adjacency list (outgoing edges) of this vertex.
     *
     * @return Vector of pointers to outgoing edges.
     */
    std::vector<Edge*> getAdj() const;

    /**
     * @brief Gets the list of incoming edges to this vertex.
     *
     * @return Vector of pointers to incoming edges.
     */
    std::vector<Edge*> getIncoming() const;

    /**
     * @brief Gets the distance of this vertex (used in graph algorithms).
     *
     * @return The distance of this vertex.
     */
    double getDist() const;

    /**
     * @brief Gets the path to this vertex (used in graph algorithms).
     *
     * @return Pointer to the path edge.
     */
    Edge* getPath() const;

    /**
     * @brief Sets the distance of this vertex.
     *
     * @param dist The distance to set.
     */
    void setDist(double dist);

    /**
     * @brief Sets the path to this vertex.
     *
     * @param path Pointer to the path edge.
     */
    void setPath(Edge* path);

    /**
     * @brief Gets the code of this vertex.
     *
     * @return The code of this vertex.
     */
    std::string getCode() const;

    /**
     * @brief Checks if this vertex is visited (used in graph algorithms).
     *
     * @return True if this vertex is visited, false otherwise.
     */
    bool isVisited() const;

    /**
     * @brief Checks if this vertex is being processed (used in graph algorithms).
     *
     * @return True if this vertex is being processed, false otherwise.
     */
    bool isProcessing() const;

    /**
     * @brief Sets the code of this vertex.
     *
     * @param code The code to set.
     */
    void setCode(std::string code);

    /**
     * @brief Sets the visited status of this vertex.
     *
     * @param visited Boolean indicating whether this vertex is visited.
     */
    void setVisited(bool visited);

    /**
     * @brief Sets the processing status of this vertex.
     *
     * @param processing Boolean indicating whether this vertex is being processed.
     */
    void setProcessing(bool processing);

    /**
     * @brief Sets the indegree of this vertex (the number of incoming edges).
     *
     * @param indegree The indegree to set.
     */
    void setIndegree(unsigned int indegree);

    /**
     * @brief Gets the indegree of this vertex.
     *
     * @return The indegree of this vertex.
     */
    unsigned int getIndegree() const;

    /**
     * @brief Sets whether this vertex is being used.
     *
     * @param Using Boolean indicating whether this vertex is being used.
     */
    void setUsing(bool Using);

    /**
     * @brief Checks if this vertex is being used.
     *
     * @return True if this vertex is being used, false otherwise.
     */
    bool isUsing() const;

protected:

    /**
     * @brief Deletes the given edge from this vertex and its adjacent vertex.
     *
     * @param edge Pointer to the edge to delete.
     * @complexity O(n1 + n2)
     * @complexity n1 = adj size
     * @complexity n2 = incoming size
     */
    void deleteEdge(Edge* edge);

    /**
     * @brief The code of the vertex.
     */
    std::string code;

    /**
     * @brief Vector of pointers to outgoing edges.
     */
    std::vector<Edge*> adj;

    /**
     * @brief Vector of pointers to incoming edges.
     */
    std::vector<Edge*> incoming;

    /**
     * @brief Pointer to the path edge (used in graph algorithms).
     */
    Edge* path = nullptr;

    /**
     * @brief Boolean indicating whether this vertex is visited (used in graph algorithms).
     */
    bool visited = false;

    /**
     * @brief Boolean indicating whether this vertex is being processed (used in graph algorithms).
     */
    bool processing = false;

    /**
     * @brief Boolean indicating whether this vertex is being used.
     */
    bool Using = true;

    /**
     * @brief The indegree of this vertex (the number of incoming edges).
     */
    unsigned int indegree = 0;

    /**
     * @brief The distance of this vertex (used in graph algorithms).
     */
    double dist = 0;

};


#endif //WATER_MANAGEMENT_VERTEX_H
