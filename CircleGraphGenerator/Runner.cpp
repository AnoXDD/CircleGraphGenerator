/**
 * The driver of the whole project
 */

#include <iostream>
#include "FileReader.h"
#include "CircleGraph.h"
#include "CircleGraphGenerator.h"

using namespace std;

int main() {
    try {
        vector<Graph> graphs; {
            // When reading the data, FileReader will also read stop words and instruction on how to group vertices. This makes the compiler recycle those memory after reading all the data
            FileReader file_reader;
            graphs = file_reader.getGraphs("data_group_containing.csv");
        }

        CircleGraphGenerator ccgenerator(graphs);
        auto circle_graph = ccgenerator.get();

        cout << circle_graph << endl;
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
    }
    system("pause");
}
