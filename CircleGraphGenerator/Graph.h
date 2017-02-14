/**
 * A basic class for holding a graph
 * 
 * Author: Runjie Guan guanrunjie@gmail.com
 */

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <ostream>
#include <functional>

using namespace std;

class GraphList;

/**
 * Hashing template from http://stackoverflow.com/questions/20953390/what-is-the-fastest-hash-function-for-pointers
 */
template <typename Tval>
struct MyHash {
    size_t operator()(const Tval* val) const {
        static const size_t shift = (size_t)log2(1 + sizeof(Tval));
        return (size_t)(val) >> shift;
    }
};

class Graph {
public:
    /**
     *  A specially designed "vertex". The last character is the type, and the other characters are the actual node
     */
    typedef string Vertex;
    /**
     * The edge should guarantee that the first is smaller than the second
     */
    typedef pair<Vertex, Vertex> Edge;

    struct EdgeHash {
        std::hash<std::string> hasher;

        size_t operator()(const Edge& e) const {
            return hasher(e.first + e.second);
        }
    };

    struct EdgeEqual {
        bool operator()(const Edge& lhs, const Edge& rhs) const {
            return lhs.first == rhs.first && lhs.second == rhs.second;
        }
    };

    typedef unordered_map<Edge, float, EdgeHash, EdgeEqual> EdgeMap;

private:
    EdgeMap list;
    unordered_map<Vertex, int> degree;

    friend ostream& operator<<(ostream&, const Graph&);
    friend class FSGGenerator;

public:
    Graph() {}
    static string convertListEntryToString(const pair<Edge, float>& p);

    /**
     * Returns if this graph has a subgraph
     */
    bool hasSubgraph(Graph& graph) const;
    /**
     * Returns if this graph has this edge
     */
    bool hasEdge(Edge& edge) const;

    /**
     * Check if this graph is an eligible graph in this graph list
     */
    bool isEligibleIn(const GraphList& graphs);

    /**
     * Adds an edge into the list. If two vertices don't exist already, create two new vertices.
     * Returns true if new edge is created
     */
    bool add(string& s1, char t1, string& s2, char t2, float weight);
    bool add(Vertex& v1, Vertex& v2, float weight);
    bool add(const Edge& e, float weight = -1);

    /**
     * To remove an edge from the list
     */
    bool remove(Vertex& v1, Vertex& v2);
    bool remove(const Edge&);

    /**
     * Set the weight of the edge
     */
    void set(const Edge& e, float new_weight);

    inline bool empty() const;
    size_t size() const;

    const EdgeMap& getList() const {
        return this->list;
    }

    /**
     * Find the difference bewteen this graph and the other graph. The weight of the larger graph is preserved
     * Returns a valid graph if the operation is valid (i.e. `g` is a subgraph of this graph), an exception will be thrown if operation is invalid
     */
    Graph operator-(const Graph& g) const;
};

ostream& operator<<(ostream& os, const Graph& g);
