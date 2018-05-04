#ifndef PUBLICTRANSPORTGRAPH_CGRAPHGENERATOR_H
#define PUBLICTRANSPORTGRAPH_CGRAPHGENERATOR_H

#include "graphformatgenerator.h"

class CGraphGenerator : public GraphFormatGenerator {
        public:
        explicit CGraphGenerator(Network&);
        bool directed() const override;
        std::set<Node *> edges(Node* source) const override ;

        protected:
        void loadNodes() override ;
    };


#endif //PUBLICTRANSPORTGRAPH_CGRAPHGENERATOR_H
