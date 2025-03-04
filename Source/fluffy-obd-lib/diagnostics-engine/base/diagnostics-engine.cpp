#include "diagnostics-engine.hpp"

bool ParametersEngine::SendCommand(const std::string& command)
{
    return m_obdAccess->Write(command);
}

std::string ParametersEngine::ReadResponse()
{
    return m_obdAccess->Read();
}

void ParametersEngine::SetSerialDevice(Obd::Device device)
{
    m_obdAccess->SetDevice(std::move(device));
}

void ParametersEngine::SetObdAccess(std::unique_ptr<Obd::ObdAccess> obdAccess)
{
    m_obdAccess = std::move(obdAccess);
}

bool ParametersEngine::OpenConnection()
{
    if (m_obdAccess) {
        return m_obdAccess->Connect();
    }
    spdlog::error("No obd device set");
    return false;
}

bool ParametersEngine::Disconnect()
{
    return m_obdAccess->Disconnect();
}

Response ParametersEngine::GetCommandResponse(ObdCommandPid pid)
{
    std::string command = m_commandRepository->getCommandByPid(pid);
    SendCommand(command);
    return m_dataParser->ParseResponse(command, ReadResponse(), pid);
}
