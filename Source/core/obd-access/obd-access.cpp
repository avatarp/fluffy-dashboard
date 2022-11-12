#include "obd-access.h"

namespace Obd {

std::string ObdAccess::Transaction(const std::string &command)
{
    this->Write(command);
    return this->Read();
}

ObdAccess::ObdAccess()
{

}

ObdAccess::~ObdAccess(){
    CloseConnection();
}

void ObdAccess::CloseConnection()
{

    if(this->m_DevicePort>0){
        close(m_DevicePort);
        std::clog << "Connection with "
                  << this->GetDevice().GetDeviceFilePath()
                  << " " << this->m_Device.GetDescription()
                  << " closed.\n";
    }
    else
        std::clog << "Connection with "
                  << this->GetDevice().GetDeviceFilePath()
                  << " " << this->m_Device.GetDescription()
                  << " was alread closed.\n";
    m_ConnectionStatus = ConnectionStatus::Disconnected;

}

bool ObdAccess::Reconnect()
{
    try
    {
        this->CloseConnection();
        this->Connect();
    }
    catch(...)
    {
        return false;
    }
    return true;
}

const Device &ObdAccess::GetDevice() const
{
    return m_Device;
}

const ConnectionStatus &ObdAccess::GetConnectionStatus() const
{
    return m_ConnectionStatus;
}
}
