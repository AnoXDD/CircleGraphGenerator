#include "CircleGraphNode.h"
#include <numeric>


CircleGraphNode::~CircleGraphNode() {
    for (auto child: children) {
        delete child;
    }
}

bool CircleGraphNode::attach(Graph& g, int max_level) {
    try {
        Graph diff = g - this->graph;

        // Test if they have something in common
        if (diff.empty()) {
            return false;
        }

        // Try to attach it to any children (if any)
        if (this->level < max_level && !this->children.empty()) {
            for (auto i = 0; i < children.size(); ++i) {
                if (children[i]->attach(diff, max_level)) {
                    return true;
                }

                if (children[i]->graph == diff) {
                    return false;
                }
            }
        }

        this->children.push_back(new CircleGraphNode(diff, this->level + 1));
        return true;
    } catch (...) {
        // Do nothing, it happens because of the first line of the try block
    }

    return false;
}

void CircleGraphNode::updateWeight(CircleGraphGenerator::EdgeFrequencyMap& freq) {
    auto& list = graph.getList();
    for (auto p : list) {
        auto& v = freq[p.first];
        // Here we use the average
        graph.set(p.first, std::accumulate(v.begin(), v.end(), 0.0) / v.size());
    }

    for (auto child : this->children) {
        child->updateWeight(freq);
    }
}
