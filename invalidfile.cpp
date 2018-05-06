#include "invalidfile.h"

InvalidFile::InvalidFile(const std::string &message) : message_(message)
{}

const char *InvalidFile::what() const noexcept
{
    return message_.c_str();
}
