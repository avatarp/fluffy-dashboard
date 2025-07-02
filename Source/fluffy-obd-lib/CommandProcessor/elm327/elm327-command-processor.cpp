#include "elm327-command-processor.hpp"

Response Elm327CommandProcessor::GetCommandResponse(ObdCommandPid pid)
{
    std::string command = m_commandRepository->getCommandByPid(pid);
    if (!SendCommand(command)) {
        spdlog::error("Failed to send command: {}", command);
        throw std::runtime_error("Failed to send command");
    }

    std::string response = ReadResponse();
    if (response.empty()) {
        spdlog::error("Received empty response for command: {}", command);
        throw std::runtime_error("Received empty response");
    }

    auto preProcessData = m_dataParser->preProcessResponse(command, response);

    Response parsedResponse;

    auto frameType = preProcessData.first;
    switch (frameType) {
    case FrameType::Single:
        parsedResponse = m_dataParser->ParseSingleFrameResponse(command, preProcessData.second, pid);
        break;
    case FrameType::First:
        parsedResponse = RetrieveMultiFrameResponse(command, preProcessData.second, pid);
        break;
    case FrameType::Consecutive:
        spdlog::error("Unexpected frame type Consecutive received");
        throw std::runtime_error("Invalid response retrieved");
    default:
        spdlog::error("Invalid response format for command: {}", command);
        throw std::runtime_error("Invalid response format");
    }

    switch (pid) {
        using enum ObdCommandPid;
    case S03:
        m_dtcHandler->ParseStoredDtc(parsedResponse);
        break;
    case S07:
        m_dtcHandler->ParsePendingDtc(parsedResponse);
        break;
    case S0A:
        m_dtcHandler->ParsePermanentDtc(parsedResponse);
        break;
    default:
        break;
    }

    return parsedResponse;
}

uint8_t Elm327CommandProcessor::GetExpectedFramesCount(ObdCommandPid pid, uint8_t dataItemsCount)
{
    // NOLINTBEGIN (cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
    switch (pid) {
    case ObdCommandPid::S03:
    case ObdCommandPid::S07:
    case ObdCommandPid::S0A:
        if ((dataItemsCount % 7U) < 3U)
            return static_cast<uint8_t>(floor(static_cast<double>(dataItemsCount) / 7.0) * 2);
        else
            return static_cast<uint8_t>(floor(static_cast<double>(dataItemsCount) / 7.0) * 2 + 1);

    case ObdCommandPid::S09P02:
        return 2; // S09P02 is expected to return 2 consecutive frames
    default:
        break;
    }
    return 0;
    // NOLINTEND (cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
}

Response Elm327CommandProcessor::RetrieveMultiFrameResponse(const std::string& command, std::smatch& match, ObdCommandPid pid)
{
    using namespace regex_groups;
    uint8_t dataItemsCount = to_uint8_t(match[dataGroupIndex].str().substr(0, 2));
    uint8_t expectedFrames = GetExpectedFramesCount(pid, dataItemsCount);

    std::string reassembledResponse { match[0].str() };

    for (uint8_t i = 0; i < expectedFrames; ++i) {

        // Send Flow Control command to ELM327 to indicate readiness for next frame
        // Send 1 frame and wait 100microseconds
        if (!SendCommand("3101F1\r")) {
            spdlog::error("Failed to send Flow Control command");
            throw std::runtime_error("Failed to send Flow Control command");
        }

        auto consecutiveResponse = ReadResponse();

        auto preProcessData = m_dataParser->preProcessConsecutiveResponse(std::to_string(i + 1)[0], consecutiveResponse);
        if (preProcessData.first != FrameType::Consecutive) {
            spdlog::error("Expected Consecutive frame type, but got: {}", static_cast<char>(preProcessData.first));
            throw std::runtime_error("Invalid response format");
        }

        reassembledResponse += preProcessData.second[4].str();
    }

    return m_dataParser->ParseMultiFrameResponse(command, match, reassembledResponse, pid);
}
