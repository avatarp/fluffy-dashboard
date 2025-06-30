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

    auto frameType = preProcessData.first;
    switch (frameType) {
    case FrameType::Single:
        return m_dataParser->ParseSingleFrameResponse(command, preProcessData.second, pid);
        break;
    case FrameType::First:
        return RetrieveMultiFrameResponse(command, preProcessData.second, pid);
        break;
    case FrameType::Consecutive:
        spdlog::error("Unexpected frame type Consecutive received");
        throw std::runtime_error("Invalid response retrieved");
    default:
        spdlog::error("Invalid response format for command: {}", command);
        throw std::runtime_error("Invalid response format");
    }
}

Response Elm327CommandProcessor::RetrieveMultiFrameResponse(const std::string& command, std::smatch& match, ObdCommandPid pid)
{
    uint8_t expectedFrames { 0 };
    if (pid == ObdCommandPid::S09P02) {
        expectedFrames = 2; // S09P03 is expected to return 2 consecutive frames
    }

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
