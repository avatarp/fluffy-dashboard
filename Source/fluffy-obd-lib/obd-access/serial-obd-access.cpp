#include "serial-obd-access.hpp"

namespace Obd {

bool UsbObdAccess::Write(const std::string& command)
{
    if (this->GetConnectionStatus() != ConnectionStatus::Connected) {
        std::cerr << "device not connected.\n";
        return false;
    }

    std::cerr << "Writing command " + command << ".\n";
    ssize_t bytesWritten = write(this->m_DevicePort,
        command.c_str(),
        command.length());

    if (bytesWritten == -1) {
        std::cerr << "WRITE FAILURE\n"
                  << "Error:"
                  << strerror(errno) << ".\n";
        m_ConnectionStatus = ConnectionStatus::ConnectionLost;
        return false;
    }

    if (command.size() == bytesWritten) {
        std::cerr << "Written "
                  << bytesWritten
                  << " bytes succesfully.\n";
        return true;
    }

    std::cerr << "Written "
              << bytesWritten
              << " bytes. Expected "
              << command.length() << ".\n";

    return false;
}

std::string UsbObdAccess::Read()
{
    std::array<char, bufferSize> readBuffer {};
    ssize_t bytesRead = read(m_DevicePort, &readBuffer, bufferSize);
    if (bytesRead <= 0) {
        std::cerr << "READ FAILURE\n"
                  << "Error:"
                  << strerror(errno) << ".\n";
        this->m_ConnectionStatus = ConnectionStatus::DeviceTimeout;
    }
    std::cerr << "Received response: "
              << readBuffer.data() << ".\n";
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
    tcflush(m_DevicePort, TCIOFLUSH);
    // Apply changes
    tcsetattr(m_DevicePort, TCSANOW, &m_Terminal);
}

void UsbObdAccess::SetDevice(Device device)
{
    if (device.GetConnectionType() != ConnectionType::Serial) {
        throw std::logic_error(std::string(
            "Invalid device set. Got"
            + std::to_string(
                static_cast<int>(device.GetConnectionType()))
            + " expected " + std::to_string(static_cast<int>(Obd::ConnectionType::Serial)))
                                   .c_str());
    }
    this->m_Device = std::move(device);
}


bool UsbObdAccess::IsDeviceFileOk()
{
    return std::filesystem::exists(this->m_Device.GetDeviceFilePath());
}

bool UsbObdAccess::OpenConnection()
{
    // NOLINTNEXTLINE
    this->m_DevicePort = open(this->m_Device.GetDeviceFilePath().c_str(),
        O_RDWR | O_NOCTTY);
    // error occured
    return this->m_DevicePort == -1;
}

bool UsbObdAccess::Connect()
{
    std::clog << "Opening connection with "
              << this->m_Device.GetDeviceFilePath()
              << " " << this->m_Device.GetDescription()
              << ".\n";

    if (!IsDeviceFileOk()) {

        std::clog << "Device file" + this->m_Device.GetDeviceFilePath() << " not found.\n";

        m_ConnectionStatus = ConnectionStatus::DeviceNotFound;
        return false;
    }

    if (!OpenConnection()) {
        this->m_ConnectionStatus = ConnectionStatus::Disconnected;
        std::clog << "Error:" << strerror(errno) << ".\n";
        return false;
    }
    
    std::clog << "OK.\n";
    this->m_ConnectionStatus = ConnectionStatus::Connected;
    return true;
}

} // namespace Obd
