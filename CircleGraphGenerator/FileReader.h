/**
 * The file reader of the circle graph
 */

#pragma once
#include <string>
#include <vector>

#include "Graph.h"

using namespace std;

class FileReader {
public:
    FileReader(string filename);
    ~FileReader();

    vector<Graph> getGraphs();
};
