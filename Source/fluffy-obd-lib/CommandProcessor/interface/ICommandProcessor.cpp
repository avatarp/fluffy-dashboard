#include "ICommandProcessor.hpp"

bool ICommandProcessor::SendCommand(const std::string& command)
{
    return m_obdAccess->Write(command);
}

std::string ICommandProcessor::ReadResponse()
{
    return m_obdAccess->Read();
}

void ICommandProcessor::SetSerialDevice(Obd::Device device)
{
    m_obdAccess->SetDevice(std::move(device));
}

void ICommandProcessor::SetObdAccess(std::unique_ptr<Obd::ObdAccess> obdAccess)
{
    m_obdAccess = std::move(obdAccess);
}

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

Response ICommandProcessor::GetCommandResponse(ObdCommandPid pid)
{
    std::string command = m_commandRepository->getCommandByPid(pid);
    SendCommand(command);
    return m_dataParser->ParseResponse(command, ReadResponse(), pid);
}

Obd::ConnectionStatus ICommandProcessor::GetConnectionStatus() const
{
    return m_obdAccess ? m_obdAccess->GetConnectionStatus() : Obd::ConnectionStatus::Disconnected;
}
