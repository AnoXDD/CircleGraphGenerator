#include "CircleGraphGenerator.h"
#include "FSGGenerator.h"
#include "CircleGraph.h"

void CircleGraphGenerator::processGraphWeight(CircleGraph& circle_graph) {
    // First, get the data of all the edges
    EdgeFrequencyMap freq;
    for (auto g : this->graphs) {
        auto &list = g.getList();
        for (auto p : list) {
            freq[p.first].push_back(p.second);
        }
    }

    // Second, process all the edges using DFS
    circle_graph.updateWeight(freq);
}

CircleGraph CircleGraphGenerator::get() {
    FSGGenerator fsg_generator( &(this->graphs));
    CircleGraph circle_graph;

    for (auto threshold = STARTING_THRESHOLD; threshold >= 0; threshold -= DELTA) {
        auto results = fsg_generator.getFSG(threshold);
        if (!results.empty()) {
            circle_graph.addLayer(results);
        }
    }

    this->processGraphWeight(circle_graph);

    return circle_graph;
}
