#include "elm327-data-parser.hpp"

Elm327DataParser::Elm327DataParser()
{
    m_decoder = std::make_shared<Elm327DataDecoder>();
}

uint8_t to_uint8_t(const std::string& str)
{
    // NOLINTNEXTLINE (readability-magic-numbers, cppcoreguidelines-avoid-magic-numbers)
    int hexBase { 16 };
    try {
        return static_cast<uint8_t>(std::stoi(str, nullptr, hexBase));
    } catch (const std::invalid_argument& e) {
        spdlog::error("Invalid argument in toUint8 conversion: {}", e.what());
    } catch (const std::out_of_range& e) {
        spdlog::error("Out of range in toUint8 conversion: {}", e.what());
    }
    return 0;
}

std::pair<FrameType, std::smatch> Elm327DataParser::preProcessResponse(const std::string& command, std::string& response)
{
    // Remove whitespaces from the response
    response.erase(remove_if(response.begin(), response.end(), isspace), response.end());

    spdlog::info("Parsing response: {}", response);

    // Define regex pattern to match the response format
    // Example: "7E8 03 41 05 4B"
    const std::regex frameRegexPattern { "(([0-9A-Z]{3})?([0-9A-F]{2}|[0-9A-F]{4}))4("
        + command.substr(1, command.size() - 2)
        + ")([0-9A-F]+)" };
    std::smatch match;

    if (regex_search(response, match, frameRegexPattern)) {

        auto responseType = match[responseSizeGroupIndex].str()[0];
        auto responseSizeLength = match[responseSizeGroupIndex].str().length();

        if (responseSizeLength == 2 && responseType == static_cast<char>(FrameType::Single)) {
            spdlog::info("Single frame response detected for command: {}", command);
            return std::make_pair(FrameType::Single, match);
        }
        if (responseSizeLength == 4 && responseType == static_cast<char>(FrameType::First)) {
            spdlog::info("Multi frame response detected for command: {}", command);
            return std::make_pair(FrameType::First, match);
        }
        if (responseSizeLength == 2 && responseType == static_cast<char>(FrameType::Consecutive)) {
            spdlog::info("Consecutive frame response detected for command: {}", command);
            return std::make_pair(FrameType::Consecutive, match);
        }
    }
    spdlog::error("Response to: {}, not matched!", command.substr(0, command.size() - 2));
    return std::make_pair(FrameType::Invalid, match);
}

std::pair<FrameType, std::smatch> Elm327DataParser::preProcessConsecutiveResponse(char expectedFrameIndex, std::string& response)
{
    // Remove whitespaces from the response
    response.erase(remove_if(response.begin(), response.end(), isspace), response.end());

    spdlog::info("Parsing response: {}", response);

    // Define regex pattern to match the consecutive frame format
    // Example: "7E8 21 52 46 52 45 56 37 44"
    const std::regex consecutiveFrameRegexPattern { "(([0-9A-Z]{3})?([0-9A-F]{2})([0-9A-F]+))" };
    std::smatch match;

    if (regex_search(response, match, consecutiveFrameRegexPattern)) {

        auto responseGroup = match[responseSizeGroupIndex].str();

        if (responseGroup.length() != 2) {
            spdlog::error("Invalid response size length! Expected 2, got: {}", responseGroup.length());
            return std::make_pair(FrameType::Invalid, match);
        }

        auto responseType = responseGroup[0];
        auto consecutiveFrameType = static_cast<char>(FrameType::Consecutive);
        auto retrievedFrameIndex = responseGroup[1];

        if (responseType == consecutiveFrameType && retrievedFrameIndex == expectedFrameIndex) {
            spdlog::info("Consecutive frame response detected with valid index {} ", expectedFrameIndex);
            return std::make_pair(FrameType::Consecutive, match);
        }
    }
    spdlog::error("Retrieved message does not match expected consecutive frame type with index {}", expectedFrameIndex);
    return std::make_pair(FrameType::Invalid, match);
}

// NOLINTNEXTLINE (bugprone-easily-swappable-parameters)
Response Elm327DataParser::ParseSingleFrameResponse(const std::string& command, std::smatch& match, ObdCommandPid pid)
{
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
        parsedResponse.raw.length = to_uint8_t(match[responseSizeGroupIndex].str());
    }

    m_decoder->decodeResponse(parsedResponse);

    return parsedResponse;
}

Response Elm327DataParser::ParseMultiFrameResponse(const std::string& command, std::smatch& match, std::string response, ObdCommandPid pid)
{
    auto pos = response.find(match[dataGroupIndex].str());
    if (pos == std::string::npos) {
        spdlog::error("Data group not found in the response: {}", match[dataGroupIndex].str());
        throw(std::runtime_error { "Data group not found in the response" });
    }
    std::string data = response.substr(pos);

    size_t constexpr dataItemCountLength { 2 };
    size_t constexpr byteLengthMultiplier { 2 }; // Each byte is represented by 2 hex characters

    if (data.length() != getExpectedResponseSizeByPid(pid) * byteLengthMultiplier + dataItemCountLength) {

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
    parsedResponse.raw.data = data;
    parsedResponse.raw.ecuId = match[ecuIdGroupIndex];
    if (match[responseSizeGroupIndex].str().size() == 4) {
        parsedResponse.raw.length = to_uint8_t(match[responseSizeGroupIndex].str().substr(1, 3));
    }

    m_decoder->decodeResponse(parsedResponse);

    return parsedResponse;
}

// NOLINTBEGIN(readability-magic-numbers, cppcoreguidelines-avoid-magic-numbers)
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
    case S09P02:
        // VIN character count is 17 characters.
        return 17;
    // GCOVR_EXCL_START
    default:
        return 0;
        // GCOVR_EXCL_STOP
    }
}
// NOLINTEND(readability-magic-numbers, cppcoreguidelines-avoid-magic-numbers)
