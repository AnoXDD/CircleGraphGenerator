#pragma once

/**
 * A class to hold a vertex in the graph
 * 
 * Author: Runjie Guan guanrunjie@gmail.com
 */

#include <string>

using namespace std;

struct Vertex {
    enum Type {Drug, Disease, Gene};

    string word;
    Type type;

    /**
     * The comparator of Vertex
     */
    inline bool operator=(const Vertex& v) const;
};
