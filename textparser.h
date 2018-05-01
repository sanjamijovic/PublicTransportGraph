#ifndef POOP_P1_TEXTPARSER_H
#define POOP_P1_TEXTPARSER_H

#include <string>
#include <fstream>
#include <utility>
#include <regex>
#include "busline.h"

class Network;

class TextParser {
public:
    explicit TextParser(Network& network);

    void collectData(const std::string& fileName);
    void collectStopsData(const std::string& fileName, BusLine* line, BusLine::Directions direction);

private:
    Network& network_;
};


#endif //POOP_P1_TEXTPARSER_H
