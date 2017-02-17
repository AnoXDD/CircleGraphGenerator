#include "GraphList.h"

#include <algorithm>

void GraphList::calculateMaxSize() {
    this->max_size = std::max_element(data->begin(), data->end(), [](Graph& lhs, Graph& rhs) {
        return lhs.size() < rhs.size();
    })->size();
}

bool GraphList::hasFrequentSubgraph(Graph& graph) const {
    int count = 0;
    for (auto full_graph : *data) {
        if (full_graph.hasSubgraph(graph)) {
            ++count;
        }
    }

    return count >= this->threshold;
}

bool GraphList::hasFrequentEdge(Graph::Edge& edge) const {
    int count = 0;
    for (auto full_graph : *data) {
        if (full_graph.hasEdge(edge)) {
            ++count;
        }
    }

    return count >= this->threshold;
}

bool GraphList::changeThresholdPercent(float threshold_percent) {
    auto old = this->threshold;
    this->threshold = std::min(static_cast<int>(ceil(threshold_percent * data->size())), static_cast<int>(data->size()));

    return old != this->threshold;
}
