#include <iostream>
#include "csvoutput.h"
#include "graphformatgenerator.h"
#include "node.h"

CsvOutput::CsvOutput(const GraphFormatGenerator & generator, const std::string & fileName, Type type)
        : OutputFileFormater(generator, fileName),
          type_(type)
{}

std::string CsvOutput::formatType() const {
    return "CSV";
}

void CsvOutput::makeFile() {
    if(file_.is_open()) {
        auto nodes = generator_.getNodes();
        switch(type_) {
            case EDGES_TABLE :
                file_ << "source;target" << std::endl;

                for(auto node : nodes) {
                    auto connectedNodes = generator_.edges(node);
                    for(auto connectedNode : connectedNodes)
                        file_ << node->label() << ";" << connectedNode->label() << std::endl;
                }
                break;
            case ADJACENCY_LIST:
                for(auto node : nodes) {
                    file_ << node->label();
                    auto connectedNodes = generator_.edges(node);
                    for (auto connectedNode : connectedNodes) {
                        file_ << ";" << connectedNode->label();

                    }
                    file_ << std::endl;
                }
                break;
            case MATRIX :

                for(auto node : nodes)
                    file_ << ";" << node->label();
                file_ << std::endl;

                for(auto node : nodes) {
                    file_ << node->label();
                    auto connectedNodes = generator_.edges(node);
                    for(auto otherNode : nodes) {
                        if(std::find(connectedNodes.begin(), connectedNodes.end(), otherNode) != connectedNodes.end())
                            file_ << ";1";
                        else
                            file_ << ";0";

                    }
                    file_ << std::endl;
                }

                break;
        }


        file_.close();
    }
    else
        std::cout << "File not found." << std::endl;
}
