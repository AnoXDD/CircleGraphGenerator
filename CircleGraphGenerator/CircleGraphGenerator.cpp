#include "CircleGraphGenerator.h"
#include "FSGGenerator.h"
#include "CircleGraph.h"

bool CircleGraphGenerator::isEqualResult(const vector<Graph>& lhs, const vector<Graph>& rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }

    for (auto i = 0; i < lhs.size(); ++i) {
        if (!(lhs[i] == rhs[i])) {
            return false;
        }
    }

    return true;
}

void CircleGraphGenerator::processGraphWeight(CircleGraph& circle_graph) {
    if (!circle_graph.getCenter()) {
        return;
    }

    // First, get the data of all the edges
    EdgeFrequencyMap freq;
    for (auto g : this->graphs) {
        auto& list = g.getList();
        for (auto p : list) {
            freq[p.first].push_back(p.second);
        }
    }

    // Second, process all the edges using DFS
    circle_graph.updateWeight(freq);
}

CircleGraph CircleGraphGenerator::get() {
    CircleGraph circle_graph;
    if (this->graphs.empty()) {
        return circle_graph;
    }

    FSGGenerator fsg_generator(&(this->graphs));

    vector<Graph> lastResult;

    for (auto threshold = STARTING_THRESHOLD; threshold >= 0; threshold -= DELTA) {
        auto results = fsg_generator.getFSG(threshold);

        // Assuming that if two results are the same, their indices are also the same
        if (!results.empty() && !this->isEqualResult(results, lastResult)) {
            circle_graph.addLayer(results); // Returns false if nothing added
        }

        std::swap(results, lastResult);
    }

    circle_graph.removeDuplicate();
    this->processGraphWeight(circle_graph);

    return circle_graph;
}
