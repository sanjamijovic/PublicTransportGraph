#include "outputfileformater.h"

OutputFileFormater::OutputFileFormater(const GraphFormatGenerator &generator, const std::string &fileName)
        : generator_(generator),
          file_(fileName) {}


