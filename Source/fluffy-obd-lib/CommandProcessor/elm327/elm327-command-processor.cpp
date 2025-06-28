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
    auto consecutiveResponse = ReadResponse();
    if (consecutiveResponse.empty()) {
        spdlog::error("Received empty response for command: {}", command);
        throw std::runtime_error("Received empty response");
    }

    auto preProcessData = m_dataParser->preProcessResponse(command, consecutiveResponse);
    if (preProcessData.first != FrameType::Consecutive) {
        spdlog::error("Expected Consecutive frame type, but got: {}", static_cast<char>(preProcessData.first));
        throw std::runtime_error("Invalid response format");
    }
    
    // TODO actual implementation for multi-frame response handling
    return Response {
        .commandPid = pid,
    };
}
