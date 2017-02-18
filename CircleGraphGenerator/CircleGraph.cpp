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
        bool success = false;
        for (auto& graph : graphs) {
            if (center->attach(graph, layers)) {
                success = true;
            }
        }

        if (!success) {
            --layers;
            return false;
        }
    }

    return true;
}

void CircleGraph::updateWeight(CircleGraphGenerator::EdgeFrequencyMap& freq) {
    this->center->updateWeight(freq);
}

void CircleGraph::removeDuplicate() {
    if (!center) {
        return;
    }

    Graph master = center->graph;
    queue<CircleGraphNode*> q;
    q.push(center);

    while (!q.empty()) {
        auto top = q.front();
        q.pop();

        auto& children = top->children;
        for (auto i = 0; i < children.size(); ++i) {
            auto& child = children[i];
            // Test if the graph of this child has anything overlapped
            auto& child_graph = child->graph.getList();

            vector<Graph::Edge> duplicates;
            for (auto p : child_graph) {
                if (master.hasEdge(p.first)) {
                    duplicates.push_back(p.first);
                }
            }

            for (auto dup : duplicates) {
                child->graph.remove(dup);
            }

            // Remove it from the list if it's empty
            if (child->graph.empty()) {
                children.erase(children.begin() + i);
                --i;
            } else {
                // Put it in the queue to finish DFS part
                q.push(child);
            }
        }

        // Add all the children graph to the master
        for (auto child : children) {
            master = master + child->graph;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const CircleGraph& graph) {
    CircleGraphNode* center = graph.getCenter();
    if (!center) {
        return os;
    }

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
