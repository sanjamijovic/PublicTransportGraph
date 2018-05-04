#ifndef PUBLICTRANSPORTGRAPH_CSVOUTPUT_H
#define PUBLICTRANSPORTGRAPH_CSVOUTPUT_H

#include "outputfileformater.h"

class CsvOutput : public OutputFileFormater {
public:
    enum Type {
        EDGES_TABLE, ADJACENCY_LIST, MATRIX
    };

    CsvOutput(const GraphFormatGenerator&, const std::string&, Type type);
    std::string formatType() const override;
    void makeFile() override;

private:
    Type type_;
};
#endif //PUBLICTRANSPORTGRAPH_CSVOUTPUT_H
