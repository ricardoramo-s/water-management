#ifndef WATER_MANAGEMENT_EDGE_H
#define WATER_MANAGEMENT_EDGE_H

#include"Vertex.h"

class Vertex;

class Edge {
public:

    Edge(Vertex *orig, Vertex *dest, double w);

    Vertex* getOrig() const;
    Vertex* getDest() const;

    double getWeight() const;
    void setFlow(double flow);
    double getFlow() const;

    void setSelected(bool selected);
    bool isSelected() const;

    void setReverse(Edge* reverse);
    Edge* getReverse() const;

    void setUsing(bool Using);
    bool isUsing() const;

protected:

    Vertex* dest;
    Vertex* orig;
    Edge* reverse = nullptr;

    double weight;
    double flow = 0;
    bool selected = false;
    bool Using = true;

};


#endif //WATER_MANAGEMENT_EDGE_H
