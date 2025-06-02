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
        if (m_DeviceFileDescriptor > Obd::stderrFileDescriptor) {
            // GCOVR_EXCL_START
            if (close(m_DeviceFileDescriptor) == -1) {
                logErrno("Error closing connection\n Error:");
                spdlog::critical("Failed to close file descriptor.");
            }
            m_DeviceFileDescriptor = 0;
            spdlog::info("Connection with {} {} closed.",
                this->m_Device.m_DeviceFilePath, this->m_Device.m_Description);
            // GCOVR_EXCL_STOP
        } else {
            spdlog::info("Connection with {} {} was already closed.",
                this->m_Device.m_DeviceFilePath, this->m_Device.m_Description);
        } // GCOVR_EXCL_START
    } catch (...) {
        logErrno("Exception during closing connection\nError: ");
        spdlog::critical("Failed to close file descriptor of device: {}",
            this->m_Device.m_DeviceFilePath);
    }
    // GCOVR_EXCL_STOP
}

bool ObdAccess::IsFileDescriptorValid()
{
    return m_DeviceFileDescriptor > stderrFileDescriptor && fcntl(m_DeviceFileDescriptor, F_GETFD) != -1;
}

// GCOVR_EXCL_START
bool ObdAccess::CloseConnection()
{
    return close(m_DeviceFileDescriptor) != -1;
} // GCOVR_EXCL_STOP

bool ObdAccess::Disconnect()
{
    try {
        if (IsFileDescriptorValid()) {
            if (!CloseConnection()) { // GCOVR_EXCL_START
                logErrno("Error closing connection\n Error:");
                spdlog::critical("Failed to close file descriptor.");
                return false;
            } // GCOVR_EXCL_STOP
            m_DeviceFileDescriptor = 0;
            spdlog::info("Connection with {} {} closed.",
                this->m_Device.m_DeviceFilePath, this->m_Device.m_Description);
        } else {
            spdlog::info("Connection with {} {} was already closed.",
                this->m_Device.m_DeviceFilePath, this->m_Device.m_Description);
            return true;
        }
    } catch (...) { // GCOVR_EXCL_START
        logErrno("Exception during closing connection\nError: ");
        spdlog::critical("Failed to close file descriptor of device: {}",
            this->m_Device.m_DeviceFilePath);
        return false;
    }
    // GCOVR_EXCL_STOP
    m_ConnectionStatus = ConnectionStatus::Disconnected;
    return true;
}

bool ObdAccess::Reconnect()
{
    try {
        this->Disconnect();
        this->Connect();
    } catch (...) { // GCOVR_EXCL_START
        spdlog::error("Failed to reconnect to device: {}", this->m_Device.m_DeviceFilePath);
        return false;
    }
    // GCOVR_EXCL_STOP
    return true;
}

const Device& ObdAccess::GetDevice() const
{
    if (m_Device.m_ConnectionType == ConnectionType::NoConnection) {
        spdlog::error("Device is not set or is invalid.");
        throw std::runtime_error("Device is not set or is invalid.");
    }
    return m_Device;
}

const ConnectionStatus& ObdAccess::GetConnectionStatus() const
{
    return m_ConnectionStatus;
}
} // namespace Obd
