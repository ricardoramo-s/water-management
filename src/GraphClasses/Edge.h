#ifndef WATER_MANAGEMENT_EDGE_H
#define WATER_MANAGEMENT_EDGE_H

#include"Vertex.h"

class Vertex;

class Edge {
public:

    /**
     * @brief Constructor with parameters.
     *
     * @param orig Pointer to the origin vertex of the edge.
     * @param dest Pointer to the destination vertex of the edge.
     * @param w The weight (capacity) of the edge.
     */
    Edge(Vertex *orig, Vertex *dest, double w);

    /**
     * @brief Gets the origin vertex of the edge.
     *
     * @return Pointer to the origin vertex.
     */
    Vertex* getOrig() const;

    /**
     * @brief Gets the weight (capacity) of the edge.
     *
     * @return The weight of the edge.
     */
    Vertex* getDest() const;

    /**
     * @brief Gets the weight (capacity) of the edge.
     *
     * @return The weight of the edge.
     */
    double getWeight() const;

    /**
     * @brief Sets the flow value of the edge.
     *
     * @param flow The flow value to set.
     */
    void setFlow(double flow);

    /**
     * @brief Gets the flow value of the edge.
     *
     * @return The flow value of the edge.
     */
    double getFlow() const;

    /**
     * @brief Sets whether the edge is selected.
     *
     * @param selected Boolean indicating whether the edge is selected.
     */
    void setSelected(bool selected);

    /**
     * @brief Checks if the edge is selected.
     *
     * @return True if the edge is selected, false otherwise.
     */
    bool isSelected() const;

    /**
     * @brief Sets the reverse edge of the current edge.
     *
     * @param reverse Pointer to the reverse edge.
     */
    void setReverse(Edge* reverse);

    /**
     * @brief Gets the reverse edge of the current edge.
     *
     * @return Pointer to the reverse edge.
     */
    Edge* getReverse() const;

    /**
     * @brief Sets whether the edge is being used.
     *
     * @param Using Boolean indicating whether the edge is being used.
     */
    void setUsing(bool Using);

    /**
     * @brief Checks if the edge is being used.
     *
     * @return True if the edge is being used, false otherwise.
     */
    bool isUsing() const;

protected:

    /**
    * @brief Pointer to the destination vertex.
    */
    Vertex* dest;

    /**
     * @brief Pointer to the origin vertex.
     */
    Vertex* orig;

    /**
     * @brief Pointer to the reverse edge.
     */
    Edge* reverse = nullptr;

    /**
     * @brief The weight (capacity) of the edge.
     */
    double weight;

    /**
     * @brief The flow value of the edge.
     */
    double flow = 0;

    /**
     * @brief Boolean indicating whether the edge is selected.
     */
    bool selected = false;

    /**
     * @brief Boolean indicating whether the edge is being used.
     */
    bool Using = true;

};


#endif //WATER_MANAGEMENT_EDGE_H
