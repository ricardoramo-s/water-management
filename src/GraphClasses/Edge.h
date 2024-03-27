//
// Created by bruno on 22/03/2024.
//

#ifndef WATER_MANAGEMENT_EDGE_H
#define WATER_MANAGEMENT_EDGE_H


template <class T>
class Edge {
public:
    Edge(Vertex<T> *orig, Vertex<T> *dest, double w);

    Vertex<T> * getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex<T> * getOrig() const;
    Edge<T> *getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Edge<T> *reverse);
    void setFlow(double flow);
protected:
    Vertex<T> * dest;
    double weight;

    bool selected = false;


    Vertex<T> *orig;
    Edge<T> *reverse = nullptr;

    double flow;
};


#endif //WATER_MANAGEMENT_EDGE_H
