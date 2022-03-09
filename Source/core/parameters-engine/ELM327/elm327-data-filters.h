#pragma once
#include <algorithm>
#include "../data-filters.h"

class Elm327DataFilters : public DataFilters
{
    bool IsDataValidForCommand(const std::string &data, const std::string &command);
    void RemoveSpaces(std::string &data);
    void RemoveMessagePrefixes(std::string &data);
    void SanitizeData(std::string &data);
public:
    virtual std::string FilterBytes(
            std::string &data,
            const std::string &command,
            const size_t &count);
private:
};

