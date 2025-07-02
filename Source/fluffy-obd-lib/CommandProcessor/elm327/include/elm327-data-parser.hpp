#ifndef ELM327_DATA_PARSER_HPP_
#define ELM327_DATA_PARSER_HPP_

#include "data-parser.hpp"
#include "elm327-data-decoder.hpp"
#include <regex>
#include <string>

#include "spdlog/spdlog.h"

namespace regex_groups {
static constexpr uint8_t ecuIdGroupIndex { 2 };
static constexpr uint8_t responseSizeGroupIndex { 3 };
static constexpr uint8_t commandPidGroupIndex { 4 };
static constexpr uint8_t dataGroupIndex { 5 };
}

uint8_t to_uint8_t(const std::string& str);

class Elm327DataParser : public DataParser {
private:
    void processResponse(Response& parsedResponse, ObdCommandPid pid);

public:
    Elm327DataParser();

    virtual std::pair<FrameType, std::smatch> preProcessResponse(const std::string& command, std::string& response);

    virtual std::pair<FrameType, std::smatch> preProcessConsecutiveResponse(char expectedFrameIndex, std::string& response);

    virtual Response ParseSingleFrameResponse(const std::string& command, std::smatch& match, ObdCommandPid pid) override;

    virtual Response ParseMultiFrameResponse(const std::string& command, std::smatch& match, std::string response, ObdCommandPid pid) override;

    static std::size_t getExpectedResponseSizeByPid(ObdCommandPid pid);
};

#endif // ELM327_DATA_PARSER_HPP_