#include "lgraphgenerator.h"
#include "network.h"
#include "busstop.h"

LGraphGenerator::LGraphGenerator(Network & network) : GraphFormatGenerator(network) {
    loadNodes();
}

bool LGraphGenerator::directed() const {
    return true;
}

// stops represent nodes
void LGraphGenerator::loadNodes() {
    for(const auto& stop : network_.allBusStops_)
        nodes_.insert(stop.second);

}

std::set<Node *> LGraphGenerator::edges(Node* source) const {
    if(dynamic_cast<BusStop *>(source) == nullptr)
        std::cout << "Pogrean tip cvora" << std::endl;
    auto stops = network_.allNextStops(dynamic_cast<BusStop *>(source));
    return std::set<Node *> (stops.begin(), stops.end());
}

