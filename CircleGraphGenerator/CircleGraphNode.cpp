#include "CircleGraphNode.h"


CircleGraphNode::~CircleGraphNode() {
    for (auto child: children) {
        delete child;
    }
}

bool CircleGraphNode::attach(Graph& g, int max_level) {
    try {
        auto diff = g - this->graph;

        if (this->level == max_level) {
            this->children.push_back(new CircleGraphNode(diff, this->level + 1));
            return true;
        }

        for (auto i = 0; i < children.size(); ++i) {
            if (children[i]->attach(diff, max_level)) {
                return true;
            }
        }
    } catch (...) {
        // Do nothing, it happens because of the first line of the try block
    }

    return false;
}
