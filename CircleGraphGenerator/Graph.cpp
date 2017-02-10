#include "Graph.h"


Graph::Graph() {}


Graph::~Graph() {}

bool Graph::add(Vertex& v1, Vertex& v2, float weight) {
    list[v1].push_back(make_pair(weight, v2));
    list[v2].push_back(make_pair(weight, v2));
}

bool Graph::empty() const {
    return this->list.empty();
}
