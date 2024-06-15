#include "serial-obd-access.hpp"

namespace Obd {

bool UsbObdAccess::Write(const std::string& command)
{
    if (this->GetConnectionStatus() != ConnectionStatus::Connected) {
        std::cerr << "Device not connected.\n";
        return false;
    }

    std::clog << "Writing command " + command << ".\n";
    ssize_t bytesWritten = write(this->m_DeviceFileDescriptor, command.c_str(), command.length());

    if (bytesWritten == -1) {
        std::cerr << "Writing failed\n"
                  << "Error:" << strerror(errno) << ".\n";
        errno = 0;
        m_ConnectionStatus = ConnectionStatus::ConnectionLost;
        return false;
    }

    if (command.size() == bytesWritten) {
        std::clog << bytesWritten << " bytes written successfully.\n";
        return true;
    }
    std::cerr << "Written " << bytesWritten << " bytes. Expected " << command.length() << ".\n";
    return false;
}

std::string UsbObdAccess::Read()
{
    std::array<char, bufferSize> readBuffer {};
    ssize_t bytesRead = read(m_DeviceFileDescriptor, &readBuffer, bufferSize);
    if (bytesRead <= 0) {
        std::cerr << "Reading failed\n"
                  << "Error:" << strerror(errno) << ".\n";
        errno = 0;
        this->m_ConnectionStatus = ConnectionStatus::DeviceTimeout;
    }
    std::clog << "Received response: " << readBuffer.data() << ".\n";
    return std::string { readBuffer.data() };
}

void UsbObdAccess::SetupDefaultTermios()
{
    // Set control flags:
    // connection speed, ignore modem control lines, enable reading
    const int baudRate = B38400;
    m_Terminal.c_cflag = baudRate | CLOCAL | CREAD;
    // Ignore framing errors and parity errors
    m_Terminal.c_iflag = IGNPAR;
    // Clear output flags
    m_Terminal.c_oflag = 0;
    // Set non-canonical mode
    m_Terminal.c_lflag &= ~ICANON;
    // Set timeout of 0.5 seconds
    m_Terminal.c_cc[VTIME] = timeout;
    // Blocking read for 0.3 second between characters
    m_Terminal.c_cc[VMIN] = readBlockingInterval;
    // Flush device file contents
    tcflush(m_DeviceFileDescriptor, TCIOFLUSH);
    // Apply changes
    tcsetattr(m_DeviceFileDescriptor, TCSANOW, &m_Terminal);
}

void UsbObdAccess::SetDevice(Device device)
{
    if (device.GetConnectionType() != ConnectionType::Serial) {
        const std::string exceptionString = std::string(
            "Invalid device set. Received "
            + std::to_string(static_cast<int>(device.GetConnectionType()))
            + " expected " + std::to_string(static_cast<int>(Obd::ConnectionType::Serial)));
        throw std::logic_error(exceptionString.c_str());
    }
    this->m_Device = std::move(device);
}

bool UsbObdAccess::IsDeviceFileOk()
{
    return std::filesystem::exists(this->m_Device.GetDeviceFilePath());
}

bool UsbObdAccess::Connect()
{
    if (!IsDeviceFileOk()) {
        std::clog << "Device file " + this->m_Device.GetDeviceFilePath() << " not found.\n";
        m_ConnectionStatus = ConnectionStatus::DeviceNotFound;
        return false;
    }

    std::clog << "Opening connection with device "
              << this->m_Device.GetDescription()
              << "\npath " << this->m_Device.GetDeviceFilePath() << ".\n";

    const int fileDescriptor = open(this->m_Device.GetDeviceFilePath().c_str(),
        O_RDWR | O_NOCTTY);

    if (fileDescriptor == -1) {
        std::clog << "Error opening obd serial device: " << strerror(errno) << ".\n";
        errno = 0;
        this->m_ConnectionStatus = ConnectionStatus::Disconnected;
        return false;
    }

    this->m_DeviceFileDescriptor = fileDescriptor;
    this->m_ConnectionStatus = ConnectionStatus::Connected;
    std::clog << "Connection successful.\n";

    return true;
}

} // namespace Obd
