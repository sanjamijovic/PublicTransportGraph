#ifndef PUBLICTRANSPORTGRAPH_LGRAPHGENERATOR_H
#define PUBLICTRANSPORTGRAPH_LGRAPHGENERATOR_H

#include "graphformatgenerator.h"

class LGraphGenerator : public GraphFormatGenerator {
public:
    explicit LGraphGenerator(Network&);
    bool directed() const override;
    std::set<Node *> edges(Node* source) const override ;

protected:
    void loadNodes() override ;
};

#endif //PUBLICTRANSPORTGRAPH_LGRAPHGENERATOR_H
