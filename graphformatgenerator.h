#ifndef PUBLICTRANSPORTGRAPH_GRAPHFORMATGENERATOR_H
#define PUBLICTRANSPORTGRAPH_GRAPHFORMATGENERATOR_H

#include <set>
class Network;
class Node;

class GraphFormatGenerator {
public:
    explicit GraphFormatGenerator(Network& network);
    virtual ~GraphFormatGenerator() = default;

    virtual bool directed() const = 0;
    std::set<Node *> getNodes() const;
    virtual std::set<Node *> edges(Node* source) const = 0;

protected:
    Network& network_;
    std::set<Node *> nodes_;

    virtual void loadNodes() = 0;
};


#endif //PUBLICTRANSPORTGRAPH_GRAPHFORMATGENERATOR_H
