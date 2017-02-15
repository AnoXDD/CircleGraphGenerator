#include "FSGGenerator.h"
#include "Graph.h"
#include "GraphList.h"

#include <numeric>
#include <algorithm>


void FSGGenerator::findSmallestFSG() {
    unordered_map<Graph::Edge, int> freq;
    for (auto graph : *graphList) {
        for (auto p : graph.list) {
            ++freq[p.first];
        }
    }

    currentFSG.clear();
    for (auto p : freq) {
        if (p.second >= this->graphList.getThreshold()) {
            Graph g;
            // Here, the weight is undefined. The final weight will be calculated in the end
            g.add(p.first);
            currentFSG.push_back(g);
        }
    }

    // Now we have currentFSG of 2-FSG
}

void FSGGenerator::generatePossibleFSG() {
    vector<Graph> possible_graphs;

    for (int i = 0; i < graphList->size() - 1; ++i) {
        for (int j = i + 1; j < graphList->size(); ++j) {
            possible_graphs.push_back(graphList->at(i) + graphList->at(j));
        }
    }

    std::swap(possible_graphs, this->currentFSG);
}

void FSGGenerator::filterEligibleFSG() {
    vector<Graph> result;
    for (auto possible_graph : this->currentFSG) {
        if (possible_graph.isEligibleIn(graphList)) {
            result.push_back(possible_graph);
        }
    }

    // Swap instead of assign values to make it faster
    std::swap(result, this->currentFSG);
}

vector<Graph> FSGGenerator::getFSG(float threshold_percent) {
    // Calculate the threshold
    this->graphList.setThresholdPercent(threshold_percent);

    findSmallestFSG();

    // Recurse to get FSG
    vector<Graph> lastFSG;
    int guardian = 0;
    while (this->currentFSG.size()) {
        // Avoid dead loop
        if (guardian++ > this->graphList.getMaxSize()) {
            throw runtime_error("Too many loops in generating FSG of threshold: " + std::to_string(threshold_percent));
        }

        generatePossibleFSG();
        filterEligibleFSG();

        lastFSG.clear();
        for (auto g : this->currentFSG) {
            if (this->graphList.hasFrequentSubgraph(g)) {
                lastFSG.push_back(g);
            }
        }

        if (lastFSG.empty()) {
            return this->currentFSG;
        }
    }

    // The only case is when findSmallestFSG() returns an empty one;
    return this->currentFSG;
}
