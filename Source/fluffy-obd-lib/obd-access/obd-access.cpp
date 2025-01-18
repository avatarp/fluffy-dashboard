#include "obd-access.hpp"

namespace Obd {

std::string ObdAccess::Transaction(const std::string& command)
{
    this->Write(command);
    return this->Read();
}

ObdAccess::~ObdAccess()
{
    if (m_DeviceFileDescriptor > 0) {
        close(m_DeviceFileDescriptor);
        std::clog << "Connection with "
                  << this->GetDevice().GetDeviceFilePath()
                  << " " << this->m_Device.GetDescription()
                  << " closed.\n";
    }
}

bool ObdAccess::CloseConnection()
{
    try {
        if (m_DeviceFileDescriptor > 0) {
            close(m_DeviceFileDescriptor);
            std::clog << "Connection with "
                      << this->GetDevice().GetDeviceFilePath()
                      << " " << this->m_Device.GetDescription()
                      << " closed.\n";
        } else {
            std::clog << "Connection with "
                      << this->GetDevice().GetDeviceFilePath()
                      << " " << this->m_Device.GetDescription()
                      << " was already closed.\n";
        }
    } catch (...) {
        std::clog << "Exception during closing connection with"
                  << this->GetDevice().GetDeviceFilePath()
                  << " " << this->m_Device.GetDescription()
                  << "\n";
    }
    m_ConnectionStatus = ConnectionStatus::Disconnected;
    return true;
}

bool ObdAccess::Reconnect()
{
    try {
        this->CloseConnection();
        this->Connect();
    } catch (...) {
        return false;
    }
    return true;
}

const Device& ObdAccess::GetDevice() const
{
    return m_Device;
}

const ConnectionStatus& ObdAccess::GetConnectionStatus() const
{
    return m_ConnectionStatus;
}
} // namespace Obd
