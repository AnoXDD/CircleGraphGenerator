/**
 * A class to generate FSG (frequent subgraphs)
 * 
 * Author: Runjie Guan guanrunjie@gmail.com
 */

#pragma once

#include <vector>
#include "Graph.h"
#include "GraphList.h"

using namespace std;

class GraphList;

class FSGGenerator {
    /* When recursively generating the FSG's, this is the variable to store the result */
    vector<Graph> currentFSG;
    GraphList graphList;

    /**
     * Find the smallest FSG, i.e. the FSG's with just an edge
     */
    void findSmallestFSG();

    void generatePossibleFSG();
    void filterEligibleFSG();

public:

    explicit FSGGenerator(vector<Graph>* g) : graphList(g) {}

    /**
     * Generates the subsequent graphs given a threshold
     */
    vector<Graph> getFSG(float threshold_percent);
};
