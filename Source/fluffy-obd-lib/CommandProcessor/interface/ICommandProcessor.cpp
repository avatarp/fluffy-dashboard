#include "ICommandProcessor.hpp"

bool ICommandProcessor::OpenConnection()
{
    if (m_obdAccess) {
        return m_obdAccess->Connect();
    }
    spdlog::error("No obd device set");
    return false;
}

bool ICommandProcessor::Disconnect()
{
    return m_obdAccess->Disconnect();
}

bool ICommandProcessor::SendCommand(const std::string& command)
{
    return m_obdAccess->Write(command);
}

std::string ICommandProcessor::ReadResponse()
{
    return m_obdAccess->Read();
}

Response ICommandProcessor::GetCommandResponse(ObdCommandPid pid)
{
    std::string command = m_commandRepository->getCommandByPid(pid);
    SendCommand(command);
    return m_dataParser->ParseResponse(command, ReadResponse(), pid);
}

void ICommandProcessor::SetObdAccess(std::shared_ptr<Obd::ObdAccess> obdAccess)
{
    m_obdAccess = std::move(obdAccess);
}

std::shared_ptr<Obd::ObdAccess> ICommandProcessor::GetObdAccess() const
{
    if (!m_obdAccess) {
        spdlog::error("ObdAccess is not set");
        throw std::runtime_error("ObdAccess is not set");
    }
    return m_obdAccess;
}
