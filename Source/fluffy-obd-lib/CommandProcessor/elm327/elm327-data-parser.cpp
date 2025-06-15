#include "elm327-data-parser.hpp"

Elm327DataParser::Elm327DataParser()
{
    m_decoder = std::make_shared<Elm327DataDecoder>();
}

Response Elm327DataParser::ParseResponse(const std::string& command, std::string response, ObdCommandPid pid)
{
    // Remove whitespaces from the response
    response.erase(remove_if(response.begin(), response.end(), isspace), response.end());

    spdlog::info("Parsing response: {}", response);

    constexpr uint8_t ecuIdGroupIndex { 2 };
    constexpr uint8_t responseSizeGroupIndex { 3 };
    constexpr uint8_t commandPidGroupIndex { 4 };
    constexpr uint8_t dataGroupIndex { 5 };

    std::smatch match;
    const std::regex singleFrameRegexPattern { "(([0-9A-Z]{3})([0-9]{2}))?4("
        + command.substr(1, command.size() - 2)
        + ")([0-9A-F]+)" };

    // Check if the response matches the expected regex pattern
    if (!std::regex_search(response, match, singleFrameRegexPattern)) {
        throw(std::runtime_error { "Response to: "
            + command.substr(0, command.size() - 2)
            + ", not matched!\n" });
    }

    if (static_cast<size_t>(match[dataGroupIndex].length()) != getExpectedResponseSizeByPid(pid) * 2) {

        const std::string exceptionMessage = "Response to: "
            + command.substr(0, command.size() - 1)
            + ", data length mismatching expected size!\nExpected: "
            + std::to_string(getExpectedResponseSizeByPid(pid) * 2)
            + ", got: " + std::to_string(match[dataGroupIndex].length());

        spdlog::error(exceptionMessage);
        throw(std::runtime_error { exceptionMessage });
    }

    Response parsedResponse;
    parsedResponse.commandPid = pid;
    parsedResponse.raw.commandId = { command[0] + match[commandPidGroupIndex].str() };
    parsedResponse.raw.data = match[dataGroupIndex];
    parsedResponse.raw.ecuId = match[ecuIdGroupIndex];
    if (!match[responseSizeGroupIndex].str().empty()) {
        parsedResponse.raw.length = static_cast<uint8_t>(std::stoi(match[responseSizeGroupIndex].str()));
    }

    m_decoder->decodeResponse(parsedResponse);

    return parsedResponse;
}

std::size_t Elm327DataParser::getExpectedResponseSizeByPid(ObdCommandPid pid)
{
    using enum ObdCommandPid;
    switch (pid) {
    case S01P04:
    case S01P05:
    case S01P06:
    case S01P07:
    case S01P08:
    case S01P09:
    case S01P0A:
    case S01P0B:
    case S01P0D:
    case S01P0E:
    case S01P0F:
    case S01P11:
    case S01P12:
    case S01P13:
    case S01P1C:
    case S01P1D:
    case S01P1E:
    case S01P2C:
    case S01P2D:
    case S01P2E:
    case S01P2F:
    case S01P30:
    case S01P33:
        return 1;

    case S01P02:
    case S01P03:
    case S01P0C:
    case S01P10:
    case S01P14:
    case S01P15:
    case S01P16:
    case S01P17:
    case S01P18:
    case S01P19:
    case S01P1A:
    case S01P1B:
    case S01P1F:
    case S01P21:
    case S01P22:
    case S01P23:
    case S01P31:
    case S01P32:
    case S01P3C:
    case S01P3D:
    case S01P3E:
    case S01P3F:
        return 2;

    case S01P00:
    case S01P01:
    case S01P20:
    case S01P24:
    case S01P25:
    case S01P26:
    case S01P27:
    case S01P28:
    case S01P29:
    case S01P2A:
    case S01P2B:
    case S01P34:
    case S01P35:
    case S01P36:
    case S01P37:
    case S01P38:
    case S01P39:
    case S01P3A:
    case S01P3B:
        // Other Pids currently not supported

    case S09P00:
        return 4;
    // GCOVR_EXCL_START
    default:
        return 0;
        // GCOVR_EXCL_STOP
    }
}
