/**
 * A basic class for holding a graph
 * 
 * Author: Runjie Guan guanrunjie@gmail.com
 */

#pragma once

#include <vector>
#include <unordered_map>
#include "Vertex.h"

using namespace std;

class Graph {
    unordered_map<Vertex, vector<pair<float, Vertex>>> list;
public:
    Graph();
    ~Graph();

    /**
     * Returns if this graph has a subgraph
     */
    bool hasSubgraph(Graph &graph);

    /**
     * Adds an edge into the list. If two vertices don't exist already, create two new vertices
     */
    bool add(Vertex &v1, Vertex &v2, float weight);

    inline bool empty() const;

    /**
     * Find the difference bewteen this graph and the other graph 
     * Returns a valid graph if the operation is valid (i.e. `g` is a subgraph of this graph), an exception will be thrown if operation is invalid
     */
    Graph operator-(const Graph& g);
};
