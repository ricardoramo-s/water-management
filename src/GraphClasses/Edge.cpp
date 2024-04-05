#include "Edge.h"

Edge::Edge(Vertex *orig, Vertex *dest, double w) {
    this->orig = orig;
    this->dest = dest;
    weight = w;
}

Vertex *Edge::getOrig() const {
    return orig;
}

Vertex *Edge::getDest() const {
    return dest;
}

double Edge::getWeight() const {
    return weight;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}

double Edge::getFlow() const {
    return flow;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

bool Edge::isSelected() const {
    return selected;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

Edge *Edge::getReverse() const {
    return reverse;
}

void Edge::setUsing(bool Using) {
    this->Using = Using;
}

bool Edge::isUsing() const {
    return Using;
}

