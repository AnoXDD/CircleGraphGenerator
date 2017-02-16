/**
 * The generator of the circle graph, which is the graph that we want to get in the end
 * 
 * Author: Runjie Guan guanrunjie@gmail.com
 */

#pragma once

#include "Graph.h"

#include <vector>
#include <unordered_map>

class CircleGraph;

class CircleGraphGenerator {
    /* The constants to hold the frequency to start and how much to decrease after that */
    const float STARTING_THRESHOLD = .8f;
    const float DELTA = .05f;

    vector<Graph> graphs;
public:

    typedef unordered_map<Graph::Edge, vector<float>, Graph::EdgeHash, Graph::EdgeEqual> EdgeFrequencyMap;

    explicit CircleGraphGenerator(vector<Graph>& g): graphs(g){}

    /**
     * Calculate the weight of all the edges
     */
    void processGraphWeight(CircleGraph&);

    CircleGraph get();
};
