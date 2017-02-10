/**
 * A class to generate FSG (frequent subgraphs)
 * 
 * Author: Runjie Guan guanrunjie@gmail.com
 */

#pragma once

#include <vector>
#include "Graph.h"

class FSGGenerator {

    /** The threshold */
    float t;

    /* When recursively generating the FSG's, this is the variable to store the result */
    vector<Graph> currentFSG;
    /* All the graphs */
    vector<Graph> *allGraphs;

    /**
     * Recursively generating next FSG
     */
    void findNextFSG();

    // Todo consider just using one function to avoid object creating
    // void generatePossible();
    // void generateEligible();

public:
    FSGGenerator(vector<Graph> *g);
    ~FSGGenerator();

    /**
     * Generates the subsequent graphs given a threshold
     */
    vector<Graph> getFSG(float threshold);
};
