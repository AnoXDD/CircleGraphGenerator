#pragma once

/**
 * The circle graph node, kind of like a tree node
 */

#include "Graph.h"
#include "CircleGraphGenerator.h"

class CircleGraph;

class CircleGraphNode {
    Graph graph;
    vector<CircleGraphNode*> children;
    /* How many parents does this node have. The initial value is zero */
    int level;

    friend std::ostream& operator<<(std::ostream& os, const CircleGraph& graph);
    friend class CircleGraph;

public:
    CircleGraphNode(Graph& g) : CircleGraphNode(g, 0) {}
    CircleGraphNode(Graph& g, int level): graph(g), level(level) {}
    ~CircleGraphNode();

    /**
     * Attaches a graph to this node. 
     * Returns true if attaching is success (i.e. this is a proper subgraph of `g`), false otherwise 
     */
    bool attach(Graph& g, int max_level);
    /**
     * Use recursion to update the frequency of the edges 
     */
    void updateWeight(CircleGraphGenerator::EdgeFrequencyMap& freq);
};
