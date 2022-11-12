#ifndef ELM327FILTERS_H
#define ELM327FILTERS_H
#include "../data-filters.h"
#include "regex"
#include "string"

class Elm327DataParser : public DataParser
{
public:
    Elm327DataParser() = default;
    virtual RawResponse ParseResponse(
            std::string data,
            const std::string &commandPid,
            const size_t &dataBytesCount);
};

#endif // ELM327FILTERS_H
