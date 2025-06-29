#ifndef DATA_FILTERS_HPP_
#define DATA_FILTERS_HPP_

#include "data-decoder.hpp"
#include "obd-command-pid.hpp"
#include "response.hpp"
#include <regex>
#include <string>

enum class FrameType : char {
    Invalid = '#',
    Single = '0',
    First = '1',
    Consecutive = '2'
};

class DataParser {
protected:
    std::shared_ptr<DataDecoder> m_decoder {};

public:
    virtual ~DataParser() { }
    virtual std::pair<FrameType, std::smatch> preProcessResponse(const std::string& command, std::string& response) = 0;
    virtual std::pair<FrameType, std::smatch> preProcessConsecutiveResponse(char expectedFrameIndex, std::string& response) = 0;

    virtual Response ParseSingleFrameResponse(const std::string& command, std::smatch& match, ObdCommandPid pid) = 0;
    virtual Response ParseMultiFrameResponse(const std::string& command, std::smatch& match, std::string response, ObdCommandPid pid) = 0;
};

#endif // DATA_FILTERS_HPP_