#ifndef ELM327FILTERS_H
#define ELM327FILTERS_H
#include "data-filters.hpp"
#include "regex"
#include "string"

class Elm327DataParser : public DataParser {
public:
    Elm327DataParser() = default;
    virtual RawResponse ParseResponse(
        std::string data,
        const size_t dataBytesCount,
        const std::string& commandPid);
};

#endif // ELM327FILTERS_H
