#include "CircleGraph.h"
#include <queue>


CircleGraph::~CircleGraph() {}

bool CircleGraph::addLayer(vector<Graph>& graphs) {
    if (!center) {
        if (graphs.size() > 1) {
            throw exception("Multiple center graphs detected. This can be resulted from a set of graphs sharing no FSGs");
        }
        this->center = new CircleGraphNode(graphs[0]);
    } else {
        ++layers;
        for (auto& graph : graphs) {
            if (!center->attach(graph, layers)) {
                return false;
            }
        }
    }

    return true;
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
        q.pop();

        for (auto child : top->children) {
            q.push(child);
        }

        if (q.empty() || q.front()->level != top->level) {
            // Start a new line because that's a new level
            os << endl;
        } else {
            os << ",";
        }
    }

    return os;
}
