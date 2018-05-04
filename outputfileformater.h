#ifndef PUBLICTRANSPORTGRAPH_OUTPUTFILEFORMATER_H
#define PUBLICTRANSPORTGRAPH_OUTPUTFILEFORMATER_H

#include <fstream>
#include <string>

class GraphFormatGenerator;


class OutputFileFormater {
public:
    OutputFileFormater(const GraphFormatGenerator&, const std::string&);
    virtual std::string formatType() const = 0;
    virtual void makeFile() = 0;

protected:
    const GraphFormatGenerator& generator_;
    std::ofstream file_;
};

#endif //PUBLICTRANSPORTGRAPH_OUTPUTFILEFORMATER_H
