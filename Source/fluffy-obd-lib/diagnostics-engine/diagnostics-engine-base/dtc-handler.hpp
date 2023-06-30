#pragma once
#include <string>
#include <vector>

// TODO DTC Handler
class DtcHandler
{
private:
    virtual std::vector<std::string> SanitizeData(std::string &data)=0;
public:
    DtcHandler();
    virtual std::vector<std::string> GetDTCs(const std::string &data)=0;
};

