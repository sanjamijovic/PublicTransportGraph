#ifndef PUBLICTRANSPORTGRAPH_GMLOUTOUT_H
#define PUBLICTRANSPORTGRAPH_GMLOUTOUT_H

#include "outputfileformater.h"

class GmlOutput : public OutputFileFormater {
public:
    GmlOutput(const GraphFormatGenerator &, const std::string &);
    std::string formatType() const override;
    virtual void makeFile() override;
};

#endif //PUBLICTRANSPORTGRAPH_GMLOUTOUT_H
