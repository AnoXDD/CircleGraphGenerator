#pragma once

#include <vector>
#include <algorithm>

#include "Graph.h"

using namespace std;

class GraphList {
    vector<Graph>* data;
    int threshold;

    /**
    * The max size of all the graphs
    */
    int max_size;
public:

    explicit GraphList(vector<Graph>* g) : data(g) {
        this->calculateMaxSize();
    }

    vector<Graph>& operator*() const {
        return *data;
    }

    vector<Graph>* operator->() const {
        return data;
    }

    void calculateMaxSize();

    /**
    * Returns if this graph meets the threshold (the numbers of graphs in *allGraphs that have `graph` as subgraph are not less than threshold)
    */
    bool hasFrequentSubgraph(Graph& graph) const;
    /**
    * Similar to hasFrequentSubgraph, returns if this edge is frequent in all the graphs
    */
    bool hasFrequentEdge(Graph::Edge& edge) const;

    float getThreshold() const {
        return this->threshold;
    }

    /**
     * Change the current threshold percent, and return if it actually changes
     */
    bool changeThresholdPercent(float threshold_percent);

    int getMaxSize() const {
        return this->max_size;
    }

};
