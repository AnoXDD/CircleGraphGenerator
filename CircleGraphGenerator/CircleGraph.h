#pragma once

/**
 * The circle graph that holds the data
 */

#include <string>
#include <vector>
#include <ostream>

#include "Graph.h"
#include "CircleGraphNode.h"
#include "CircleGraphGenerator.h"

using namespace std;

class CircleGraph {

    CircleGraphNode* center;
    int layers; // todo init = 0

public:
    CircleGraph(): center(nullptr), layers(0) {}
    ~CircleGraph();

    /**
     * Adds a new layer of graph. Returns true if a new layer is added
     */
    bool addLayer(vector<Graph>& g);

    CircleGraphNode* getCenter() const {
        return center;
    }

    /**
     * Update the weight of all the edges of this circle graph
     */
    void updateWeight(CircleGraphGenerator::EdgeFrequencyMap& freq);
};

std::ostream& operator<<(std::ostream& os, const CircleGraph& graph);
