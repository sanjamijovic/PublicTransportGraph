#ifndef PUBLICTRANSPORTGRAPH_TEXTPARSER_H
#define PUBLICTRANSPORTGRAPH_TEXTPARSER_H

#include <string>
#include <fstream>
#include <utility>
#include <regex>
#include "busline.h"

class Network;

class TextParser {
public:
    explicit TextParser(Network& network);

    void collectData(const std::string& fileName, bool& valid);
    void collectStopsData(const std::string& fileName, BusLine* line, BusLine::Directions direction);

private:
    Network& network_;
};


#endif //PUBLICTRANSPORTGRAPH_TEXTPARSER_H
