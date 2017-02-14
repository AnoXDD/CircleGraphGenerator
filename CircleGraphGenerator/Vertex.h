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

    Vertex(string word, Type type): word(word), type(type) {}

    /**
     * The comparator of Vertex
     */
    bool operator==(const Vertex& v) const {
        return this->word == v.word && this->type == v.type;
    }
};
