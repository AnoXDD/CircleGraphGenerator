#pragma once

/**
 * The circle graph that holds the data
 */

#include <string>
#include <vector>

#include "Graph.h"
#include "CircleGraphNode.h"

using namespace std;

class CircleGraph {

    CircleGraphNode* center;
    int layers; // todo init = 0

public:
    CircleGraph();
    ~CircleGraph();

    /**
     * Return the circle graph in the string form
     */
    string getString();

    /**
     * Adds a new layer of graph
     */
    void addLayer(vector<Graph>& g);
};
