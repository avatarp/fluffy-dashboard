#include "elm327-data-filters.h"
#include <iostream>

bool Elm327DataFilters::IsDataValidForCommand(const std::string &data,
                                              const std::string &command)
{
    if(command.size() == 4 || command.size() == 2)
    {
        std::regex pattern('4' + command.substr(1, command.size() - 1));
        std::smatch match;
        return std::regex_search(data, match, pattern);
    }
    return true;
}

void Elm327DataFilters::RemoveSpaces(std::string &data)
{
    data.erase(std::remove(data.begin(), data.end(), ' '), data.end());
}

void Elm327DataFilters::RemoveMessagePrefixes(std::string &data)
{
    const std::regex messagePrefix("[0-9]:");
    std::string result;
    std::regex_replace(std::back_inserter(result), data.begin(), data.end(), messagePrefix, "");
    data = std::move(result);
}

void Elm327DataFilters::SanitizeData(std::string &data)
{
    RemoveSpaces(data);
    RemoveMessagePrefixes(data);
}


std::string Elm327DataFilters::FilterBytes(std::string &data,
                                           const std::string &command,
                                           const size_t &count)
{
    SanitizeData(data);
    if(IsDataValidForCommand(data, command)==false)
        return "";

    std::regex pattern(
                '4' + command.substr(1, command.size() - 1) + "([0-9A-Z]+)");
    std::smatch match;

    if(std::regex_search(data, match, pattern) && match.str(1).size() == count*2)
        return match[1];
    else
        return "";
}
