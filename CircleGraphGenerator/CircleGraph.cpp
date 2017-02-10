#include "CircleGraph.h"


CircleGraph::CircleGraph() {}


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
