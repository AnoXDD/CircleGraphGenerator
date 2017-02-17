#include "FSGGenerator.h"
#include "Graph.h"
#include "GraphList.h"

#include <numeric>
#include <algorithm>
#include <unordered_map>


void FSGGenerator::findSmallestFSG() {
    unordered_map<Graph::Edge, int, Graph::EdgeHash, Graph::EdgeEqual> freq;
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

void FSGGenerator::removeDuplicateFSG() {
    vector<Graph> uniques;

    // Use the naive way to do this, but may be faster than unordered_map
    for (int i = 0; i < this->currentFSG.size(); ++i) {
        auto j = 0;
        for (; j < uniques.size(); ++j) {
            if (currentFSG[i] == currentFSG[j]) {
                break;
            }
        }
        // No break
        if (j == uniques.size()) {
            uniques.push_back(currentFSG[i]);
        }
    }

    std::swap(uniques, this->currentFSG);
}

void FSGGenerator::generatePossibleFSG(int current_size) {
    vector<Graph> possible_graphs;

    if (currentFSG.size() == 1) {
        auto& graph = currentFSG[0];

        for (auto& raw_graph : *graphList) {
            if (raw_graph.hasSubgraph(graph)) {
                // For each raw graph, add an edge to the graph
                auto diff = raw_graph - graph;
                auto& edges = diff.getList();
                for (auto p:edges) {
                    auto g(graph);
                    g.add(p.first);
                    possible_graphs.push_back(g);
                }
            }
        }
    } else {
        for (int i = 0; i < static_cast<int>(currentFSG.size()) - 1; ++i) {
            for (int j = i + 1; j < currentFSG.size(); ++j) {
                auto result = currentFSG[i] + currentFSG[j];
                if (result.edgeSize() == current_size) {
                    possible_graphs.push_back(currentFSG[i] + currentFSG[j]);
                }
            }
        }
    }

    std::swap(possible_graphs, this->currentFSG);
}

void FSGGenerator::filterEligibleFSG() {
    //    vector<Graph> result;
    //    for (auto possible_graph : this->currentFSG) {
    //        if (possible_graph.edgeSize() == current_size) {
    ////            if (possible_graph.isEligibleIn(graphList)) {
    //                result.push_back(possible_graph);
    ////            }
    //        }
    //    }
    //
    //    // Swap instead of assign values to make it faster
    //    std::swap(result, this->currentFSG);

    removeDuplicateFSG();
}

vector<Graph> FSGGenerator::getFSG(float threshold_percent) {
    // Calculate the threshold
    if (!this->graphList.changeThresholdPercent(threshold_percent)) {
        // Not changed
        return vector<Graph>{};
    }

    // Return immediately if there is only one graph or the threshold is one, which means every graph meets the criteria
    if (this->graphList->size() == 1) {
        return *this->graphList;
    } 
    if(this->graphList.getThreshold() <= 1) {
        // Filter out the graphs that are smaller than currentFSG
        if (!this->currentFSG.empty()) {
            auto edge_size = this->currentFSG[0].edgeSize();
            vector<Graph> graphs;

            for (auto &g : *this->graphList) {
                if (g.edgeSize() > edge_size) {
                    graphs.push_back(g);
                }
            }

            return graphs;
        }

        return *this->graphList;
    }

    if (this->currentFSG.empty()) {
        findSmallestFSG();
    }

    // Recurse to get FSG
    vector<Graph> lastFSG;
    int guardian = 0;
    do {
        // Avoid dead loop
        if (guardian++ > this->graphList.getMaxSize()) {
            break;
            //            throw runtime_error("Too many loops in generating FSG of threshold: " + std::to_string(threshold_percent));
        }

        generatePossibleFSG(this->currentFSG[0].edgeSize() + 1);
        //        filterEligibleFSG(); 
        removeDuplicateFSG();

        lastFSG.clear();
        for (auto g : this->currentFSG) {
            if (this->graphList.hasFrequentSubgraph(g)) {
                lastFSG.push_back(g);
            }
        }

        if (lastFSG.empty()) {
            break;
        }

        std::swap(this->currentFSG, lastFSG);
    } while (this->currentFSG.size() > 1);

    // The only case is when findSmallestFSG() returns an empty one;
    removeDuplicateFSG();
    return this->currentFSG;
}
