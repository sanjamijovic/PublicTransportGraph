#ifndef INVALIDFILE_H
#define INVALIDFILE_H

#include <exception>
#include <string>

class InvalidFile : public std::exception {
public:
    InvalidFile(const std::string &message);
    const char *what() const noexcept;

private:
    std::string message_;
};

#endif // INVALIDFILE_H
