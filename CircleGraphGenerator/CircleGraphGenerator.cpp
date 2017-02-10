#include "CircleGraphGenerator.h"
#include "FSGGenerator.h"


CircleGraphGenerator::~CircleGraphGenerator()
{
    delete center;
}

CircleGraph CircleGraphGenerator::get() {
    FSGGenerator fsg_generator(&(this->graphs));
    CircleGraph circle_graph;

    for (auto threshold = STARTING_THRESHOLD; threshold >= 0; threshold -= DELTA) {
        auto results = fsg_generator.getFSG(threshold);
        if (!results.empty()) {
            circle_graph.addLayer(results);
        } 
    }

    return circle_graph;
}
