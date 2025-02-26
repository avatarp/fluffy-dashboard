#include "serial-obd-access.hpp"

namespace Obd {

bool UsbObdAccess::Write(const std::string& command)
{
    if (this->GetConnectionStatus() != ConnectionStatus::Connected) {
        spdlog::error("Device not connected.");
        return false;
    }
    // GCOVR_EXCL_START
    spdlog::info("Writing command: {}", command);
    ssize_t bytesWritten = write(m_DeviceFileDescriptor, command.c_str(), command.length());

    if (bytesWritten == -1) {
        logErrno("WRITE FAILURE\n Error:");
        m_ConnectionStatus = ConnectionStatus::ConnectionLost;
        return false;
    }

    if (command.size() == static_cast<size_t>(bytesWritten)) {
        spdlog::info("Written {} bytes successfully.", bytesWritten);
        return true;
    }

    spdlog::error("Error! Written {} bytes. Expected {}.", bytesWritten, command.length());
    return false;
}
// GCOVR_EXCL_STOP

// GCOVR_EXCL_START
std::string UsbObdAccess::Read()
{
    std::array<char, bufferSize> readBuffer {};
    ssize_t bytesRead = read(m_DeviceFileDescriptor, &readBuffer, bufferSize);

    if (bytesRead <= 0) {
        logErrno("READ FAILURE\n Error:");
        this->m_ConnectionStatus = ConnectionStatus::DeviceTimeout;
    }

    spdlog::info("Received response: {}", readBuffer.data());
    return std::string { readBuffer.data() };
}
// GCOVR_EXCL_STOP

// GCOVR_EXCL_START
bool UsbObdAccess::ApplyDefaultConnectionSettings()
{
    errno = 0;
    // Set control flags:
    // connection speed, ignore modem control lines, enable reading
    const int baudRate = B38400;
    m_Terminal.c_cflag = baudRate | CLOCAL | CREAD;
    // Ignore framing errors and parity errors
    m_Terminal.c_iflag = IGNPAR;
    // Clear output flags
    m_Terminal.c_oflag = 0;
    // Set non-canonical mode
    // Warning -Wsign-conversion suppressed due to standard way of disabling canonical mode
#pragma GCC diagnostic ignored "-Wsign-conversion"
    m_Terminal.c_lflag &= (~ICANON);
#pragma GCC diagnostic warning "-Wsign-conversion"
    // Set timeout of 0.5 seconds
    m_Terminal.c_cc[VTIME] = timeout;
    // Blocking read for 0.3 second between characters
    m_Terminal.c_cc[VMIN] = readBlockingInterval;
    // Flush device file contents
    tcflush(m_DeviceFileDescriptor, TCIOFLUSH);
    // Apply changes
    tcsetattr(m_DeviceFileDescriptor, TCSANOW, &m_Terminal);
    return (errno == 0);
}
// GCOVR_EXCL_STOP

void UsbObdAccess::SetDevice(Device device)
{
    if (device.m_ConnectionType != ConnectionType::Serial) {
        throw std::logic_error(std::string(
            "Invalid device set. Got"
            + std::to_string(
                static_cast<int>(device.m_ConnectionType))
            + " expected " + std::to_string(static_cast<int>(Obd::ConnectionType::Serial)))
                                   .c_str());
    }
    this->m_Device = std::move(device);
}

bool UsbObdAccess::IsDeviceFileOk()
{
    return std::filesystem::exists(this->m_Device.m_DeviceFilePath);
}

// GCOVR_EXCL_START
bool UsbObdAccess::OpenConnection()
{
    // NOLINTNEXTLINE
    m_DeviceFileDescriptor = open(m_Device.m_DeviceFilePath.c_str(), O_RDWR | O_NOCTTY);
    // error occurred
    return m_DeviceFileDescriptor == -1;
}
// GCOVR_EXCL_STOP

bool UsbObdAccess::Connect()
{
    spdlog::info("Opening connection with {} {}.", this->m_Device.m_DeviceFilePath, this->m_Device.m_Description);

    if (!IsDeviceFileOk()) {
        spdlog::error("Device file" + this->m_Device.m_DeviceFilePath + " not found.");

        m_ConnectionStatus = ConnectionStatus::DeviceNotFound;
        return false;
    }

    if (!OpenConnection()) {
        this->m_ConnectionStatus = ConnectionStatus::Disconnected;
        logErrno("Failed to open connection\n Error:");
        return false;
    }

    spdlog::info("Connection opened successfully.");

    this->m_ConnectionStatus = ConnectionStatus::Connected;
    return true;
}

} // namespace Obd
