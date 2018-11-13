#include "graphformatgenerator.h"

GraphFormatGenerator::GraphFormatGenerator(Network &network) : network_(network) {}

std::set<Node *> GraphFormatGenerator::getNodes() const {
    return nodes_;
}
