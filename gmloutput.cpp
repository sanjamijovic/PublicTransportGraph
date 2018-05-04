#include "gmloutput.h"
#include "graphformatgenerator.h"
#include "node.h"
#include <iostream>

GmlOutput::GmlOutput(const GraphFormatGenerator & generator, const std::string & fileName)
        : OutputFileFormater(generator, fileName)
{}

std::string GmlOutput::formatType() const {
    return "GML";
}

void GmlOutput::makeFile() {
    if(file_.is_open()) {
        auto nodes = generator_.getNodes();
        file_  << "graph" << std::endl << "[" << std::endl;
        for(auto node : nodes) {
            file_ << "\tnode" << std::endl << "\t[" << std::endl;
            file_ << "\t\t" << "id "<< node->label() << std::endl;
            file_ << "\t\tlabel " << node->label() << std::endl;
            file_ << "\t]" << std::endl;
        }

        for(auto node : nodes) {
            auto connectedNodes = generator_.edges(node);
            for(auto connectedNode : connectedNodes) {
                file_ << "\tedge" << std::endl << "\t[" << std::endl << "\t\t" << "source " << node->label() << std::endl
                      << "\t\t"<< "target " << connectedNode->label() << std::endl << "\t]" << std::endl;
            }
        }
        file_ << "]" << std::endl;
        file_.close();
    } else
        std::cout << "File not found." << std::endl;
}
