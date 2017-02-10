/**
 * The generator of the circle graph, which is the graph that we want to get in the end
 * 
 * Author: Runjie Guan guanrunjie@gmail.com
 */

#pragma once

#include <vector>

#include "CircleGraph.h"
#include "Graph.h"

class CircleGraphGenerator {
    /* The constants to hold the frequency to start and how much to decrease after that */
    const float STARTING_THRESHOLD = .8f;
    const float DELTA = .05f;

    vector<Graph> graphs;
public:
    explicit CircleGraphGenerator(vector<Graph>& g): graphs(g){}
    ~CircleGraphGenerator();

    CircleGraph get();
};
