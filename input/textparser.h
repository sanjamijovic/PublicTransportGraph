#ifndef PUBLICTRANSPORTGRAPH_TEXTPARSER_H
#define PUBLICTRANSPORTGRAPH_TEXTPARSER_H

#include "busline.h"
#include <fstream>
#include <regex>
#include <string>
#include <utility>

class Network;

class TextParser {
public:
    explicit TextParser(Network &network);

    void collectData(const std::string &fileName, bool &valid);
    void collectStopsData(const std::string &fileName, BusLine *line, BusLine::Directions direction);

private:
    Network &network_;
};

#endif //PUBLICTRANSPORTGRAPH_TEXTPARSER_H
