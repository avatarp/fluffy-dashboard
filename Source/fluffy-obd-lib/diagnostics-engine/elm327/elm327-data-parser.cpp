#include "elm327-data-parser.hpp"

RawResponse Elm327DataParser::ParseResponse(std::string data,
    const size_t dataBytesCount,
    const std::string& commandPid)
{
    data.erase(remove_if(data.begin(), data.end(), isspace), data.end());
    std::clog << "parsing response:" << data << '\n';

    constexpr uint8_t ecuIdGroupIndex { 2 };
    constexpr uint8_t responseSizeGroupIndex { 3 };
    constexpr uint8_t commandPidGroupIndex { 4 };
    constexpr uint8_t dataGroupIndex { 5 };

    const std::regex responseRegexPattern { "(([0-9A-Z]{3})([0-9]{2}))?4("
        + commandPid.substr(1, 3)
        + ")([0-9A-F]+)" };
    std::smatch match;

    if (std::regex_search(data, match, responseRegexPattern)) {

        if (static_cast<size_t>(match[dataGroupIndex].length()) != dataBytesCount * 2) {

            throw(std::runtime_error { "Response to: " + commandPid.substr(0, commandPid.size()) + ", data length mismatching expected size!\n" });
        }

        RawResponse parsedResponse;
        parsedResponse.m_commandId = { commandPid[0] + match[commandPidGroupIndex].str() };
        parsedResponse.m_data = match[dataGroupIndex];
        parsedResponse.m_ecuId = match[ecuIdGroupIndex];
        if (!match[responseSizeGroupIndex].str().empty()) {
            parsedResponse.m_length = static_cast<uint8_t>(std::stoi(match[responseSizeGroupIndex].str()));
        }
        return parsedResponse;
    }
    throw(std::runtime_error { "Response to: "
        + commandPid.substr(0, commandPid.size() - 1)
        + ", not matched!\n" });
}
