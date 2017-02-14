#include "CircleGraph.h"
#include <queue>


CircleGraph::~CircleGraph() {}

void CircleGraph::addLayer(vector<Graph>& graphs) {
    if (!center) {
        if (graphs.size() > 1) {
            throw exception("Multiple centers detected");
        }
        this->center = new CircleGraphNode(graphs[0]);
    } else {
        ++layers;
        for (auto& graph : graphs) {
            center->attach(graph, layers);
        }
    }
}

void CircleGraph::updateWeight(CircleGraphGenerator::EdgeFrequencyMap& freq) {
    this->center->updateWeight(freq);
}

std::ostream& operator<<(std::ostream& os, const CircleGraph& graph) {
    CircleGraphNode* center = graph.getCenter();
    queue<CircleGraphNode*> q;
    q.push(center);

    while (!q.empty()) {
        auto top = q.front();
        os << top->graph;

        if (q.front()->level != top->level) {
            // Start a new line because that's a new level
            os << endl;
        } else {
            os << ",";
        }

        for (auto child: top->children) {
            q.push(child);
        }
    }

    return os;
}
