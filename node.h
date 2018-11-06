#ifndef PUBLICTRANSPORTGRAPH_NODE_H
#define PUBLICTRANSPORTGRAPH_NODE_H

class Node {
public:
    virtual std::string label() const = 0;

    virtual ~Node() = default;
};

#endif //PUBLICTRANSPORTGRAPH_NODE_H
