#pragma once
#include <string>
#include <regex>

class DataFilters
{
public:
    virtual ~DataFilters(){}
    virtual std::string FilterBytes(
            std::string &data,
            const std::string &command,
            const size_t &count) = 0;
};

