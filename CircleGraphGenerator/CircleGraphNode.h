#pragma once

/**
 * The circle graph node, kind of like a tree node
 */

#include "Graph.h"

class CircleGraphNode {
    Graph graph;
    vector<CircleGraphNode*> children;
    /* How many parents does this node have. The initial value is zero */
    int level;

public:
    CircleGraphNode(Graph& g) : CircleGraphNode(g, 0) {}
    CircleGraphNode(Graph& g, int level): graph(g), level(level) {}
    ~CircleGraphNode();

    /**
     * Attaches a graph to this node. 
     * Returns true if attaching is success (i.e. this is a subgraph of `g`), false otherwise   
     */
    bool attach(Graph &g, int max_level);
};
