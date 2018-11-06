#include "cgraphgenerator.h"

#include "network.h"
#include "busline.h"

CGraphGenerator::CGraphGenerator(Network &network) : GraphFormatGenerator(network) {
    loadNodes();
}

bool CGraphGenerator::directed() const {
    return false;
}

// stops represent nodes
void CGraphGenerator::loadNodes() {
    for (auto line : network_.busLines_)
        nodes_.insert(line);

}

std::set<Node *> CGraphGenerator::edges(Node *source) const {
    std::set <Node *> result;
    if (dynamic_cast<BusLine *>(source) == nullptr)
        std::cout << "Pogresan tip cvora" << std::endl;
    auto lines = dynamic_cast<BusLine *>(source)->linesWithMutualStops();
    for (auto line : lines)
        if (*dynamic_cast<BusLine *>(source) < *line)
            result.insert(line);
    return result;
}
