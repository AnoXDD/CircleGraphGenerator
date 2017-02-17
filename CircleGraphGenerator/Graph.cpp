#include "Graph.h"
#include "CircleGraphNode.h"
#include "GraphList.h"

string Graph::convertListEntryToString(const pair<Edge, float>& p) {
    auto v1 = p.first.first;
    auto v1t = v1.back();
    auto v2 = p.first.second;
    auto v2t = v2.back();

    v1.back() = '(';
    v2.back() = '(';

    return "{" + v1 + v1t + ")|" + std::to_string(p.second) + "|" + v2 + v2t + ")}";
}

bool Graph::hasSubgraph(Graph& graph) const {
    if (this->size() < graph.size()) {
        return false;
    }

    for (auto pair : graph.list) {
        if (!this->list.count(pair.first)) {
            // The edge doesn't exist 
            return false;
        }
    }

    return true;
}

bool Graph::hasEdge(const Edge& edge) const {
    return list.count(edge);
}

bool Graph::isEligibleIn(const GraphList& graphList) {
    // Remove each vertex from the graph temporarily, one at a time
    for (auto& vertex_pair : degree) {
        // Find the edges not containing this vertex
        auto hiding_vertex = vertex_pair.first;

        for (auto& edge_pair : list) {
            auto edge = edge_pair.first;
            if (edge.first != hiding_vertex && edge.second != hiding_vertex) {
                // This edge is to be included and tested
                if (!graphList.hasFrequentEdge(edge)) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Graph::add(string& s1, char t1, string& s2, char t2, float weight) {
    return this->add(s1 += t1, s2 += t2, weight);
}

bool Graph::add(Vertex& v1, Vertex& v2, float weight) {
    if (v1 > v2) {
        std::swap(v1, v2);
    }

    Edge e = make_pair(v1, v2);
    return this->add(e, weight);
}

bool Graph::add(const Edge& e, float weight) {
    list[e] += weight;

    ++degree[e.first];
    ++degree[e.second];

    return list[e] == weight;
}

bool Graph::remove(Vertex& v1, Vertex& v2) {
    if (v1 > v2) {
        std::swap(v1, v2);
    }

    Edge e = make_pair(v1, v2);
    return this->remove(e);
}

bool Graph::remove(const Edge& e) {
    if (--degree[e.first] < 0) {
        degree.erase(e.first);
    }
    if (--degree[e.second] < 0) {
        degree.erase(e.second);
    }

    return list.erase(e);
}

void Graph::set(const Edge& e, float new_weight) {
    this->list[e] = new_weight;
}

bool Graph::empty() const {
    return this->list.empty();
}

size_t Graph::size() const {
    return degree.size();
}

Graph Graph::operator-(const Graph& g) const {
    Graph result(*this);

    for (auto p : g.list) {
        if (!result.remove(p.first)) {
            throw std::invalid_argument("The difference cannot be calculated because one is not the subgraph of the other");
        }
    }

    return result;
}

Graph Graph::operator+(const Graph& g) const {
    Graph result(*this);

    for (auto edge_pair: g.list) {
        auto& edge = edge_pair.first;
        if (!result.hasEdge(edge)) {
            result.add(edge);
        }
    }

    return result;
}

bool Graph::operator==(const Graph& g) const {
    if (this->list.size() != g.list.size()) {
        return false;
    }

    for (auto p : g.list) {
        if (!this->hasEdge(p.first)) {
            return false;
        }
    }

    return true;
}

ostream& operator<<(ostream& os, const Graph& g) {
    os << "[";
    for (auto p : g.list) {
        os << Graph::convertListEntryToString(p);
    }
    return os << "]";
}
