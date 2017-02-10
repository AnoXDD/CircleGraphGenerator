/**
 * The driver of the whole project
 */

#include <iostream>
#include "FileReader.h"
#include "CircleGraph.h"
#include "CircleGraphGenerator.h"

using namespace std;

int main() {
    cout << "Hello world" << endl;

    FileReader file_reader("data");
    auto graphs = file_reader.getGraphs();

    CircleGraphGenerator ccgenerator(graphs);
    auto circle_graph = ccgenerator.get();

    cout << circle_graph.getString() << endl;
}