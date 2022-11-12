#pragma once
#include <string>
#include <regex>
#include "response.h"

class DataParser
{
public:
    virtual ~DataParser(){}
    virtual RawResponse ParseResponse(
            std::string data,
            const std::string &commandPid,
            const size_t &dataBytesCount) = 0;
};
