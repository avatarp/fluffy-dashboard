#include "obd-access.hpp"

namespace Obd {

std::string ObdAccess::Transaction(const std::string& command)
{
    this->Write(command);
    return this->Read();
}

ObdAccess::~ObdAccess()
{
    try {
        if (m_DeviceFileDescriptor > 0) {

            if (close(m_DeviceFileDescriptor) == -1) {
                logErrno("Error closing connection\n Error:");
                spdlog::critical("Failed to close file descriptor.");
            }
            m_DeviceFileDescriptor = 0;
            spdlog::info("Connection with {} {} closed.",
                this->m_Device.GetDeviceFilePath(), this->m_Device.GetDescription());
        } else {
            spdlog::info("Connection with {} {} was already closed.",
                this->m_Device.GetDeviceFilePath(), this->m_Device.GetDescription());
        }
    } catch (...) {
        logErrno("Exception during closing connection\nError: ");
        spdlog::critical("Failed to close file descriptor of device: {}",
            this->m_Device.GetDeviceFilePath());
    }
}

bool ObdAccess::IsFileDescriptorValid()
{
    return m_DeviceFileDescriptor > 0;
}

bool ObdAccess::Disconnect()
{
    return close(m_DeviceFileDescriptor) != -1;
}

bool ObdAccess::CloseConnection()
{
    try {
        if (IsFileDescriptorValid()) {

            if (!Disconnect()) {
                logErrno("Error closing connection\n Error:");
                spdlog::critical("Failed to close file descriptor.");
                return false;
            }
            m_DeviceFileDescriptor = 0;
            spdlog::info("Connection with {} {} closed.",
                this->m_Device.GetDeviceFilePath(), this->m_Device.GetDescription());
        } else {
            spdlog::info("Connection with {} {} was already closed.",
                this->m_Device.GetDeviceFilePath(), this->m_Device.GetDescription());
            return false;
        }
    } catch (...) {
        logErrno("Exception during closing connection\nError: ");
        spdlog::critical("Failed to close file descriptor of device: {}",
            this->m_Device.GetDeviceFilePath());
        return false;
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
        spdlog::error("Failed to reconnect to device: {}", this->m_Device.GetDeviceFilePath());
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
