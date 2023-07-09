#include "logging.hpp"

std::string getStrerror(int errorNumber)
{
    constexpr size_t bufferSize { 256 };
    char buffer[bufferSize]; // NOLINT
    std::string errorStr { strerror_r(errorNumber, buffer, bufferSize) };
    return errorStr;
}