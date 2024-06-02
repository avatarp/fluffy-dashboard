#include "elm327-data-parser.hpp"

RawResponse Elm327DataParser::ParseResponse(std::string data,
    const size_t& dataBytesCount,
    const std::string& commandPid)
{
    data.erase(remove_if(data.begin(), data.end(), isspace), data.end());

    std::smatch match;
    std::regex dataBytesPattern { "([0-9A-Z]{3,3})([0-9]{2,2})(4"
        + commandPid.substr(1, 3)
        + ")([0-9A-F]+)" };

    if (std::regex_search(data, match, dataBytesPattern)) {
        if (match[4].length() != dataBytesCount * 2) {
            throw(std::runtime_error { "Response to: " + commandPid.substr(0, commandPid.size() - 1) + ", not found!\n" });
        }

        RawResponse parsedResponse;
        parsedResponse.m_commandId = match[3];
        parsedResponse.m_data = match[4];
        parsedResponse.m_ecuId = match[1];
        parsedResponse.m_length = std::stoi(match[2]);

        return parsedResponse;
    }
    throw(std::runtime_error { "Response to: "
        + commandPid.substr(0, commandPid.size() - 1)
        + ", not matched!\n" });
}
