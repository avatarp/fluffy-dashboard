#pragma once
#include <string>
#include <regex>
#include "response.hpp"

class DataParser
{
public:
    virtual ~DataParser(){}
    virtual RawResponse ParseResponse(
            std::string data,
            const size_t &dataBytesCount,
            const std::string &commandPid) = 0;
};
