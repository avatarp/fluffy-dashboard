#include "bluetooth-obd-access.hpp"

namespace Obd {

bool BluetoothObdAccess::Write(const std::string& command)
{
    if (this->GetConnectionStatus() != ConnectionStatus::Connected) {
        std::cerr << "device not connected.\n";
        return false;
    }

    std::cerr << "Writing command " + command << ".\n";
    ssize_t bytesWritten = write(
        this->m_DevicePort, command.c_str(), command.length());

    if (bytesWritten == -1) {
        std::cerr << "WRITE FAILURE\n"
                  << "Error:" << getStrerror(errno) << ".\n";
        m_ConnectionStatus = ConnectionStatus::ConnectionLost;
        return false;
    }

    if (command.size() == bytesWritten) {
        std::cerr << "Written " << bytesWritten << " bytes succesfully.\n";
        return true;
    }

    std::clog << "Written " << bytesWritten << " bytes. Expected "
              << command.length() << ".\n";

    return false;
}

std::string BluetoothObdAccess::Read()
{
    std::array<char, bufferSize> readBuffer {};
    ssize_t bytesRead = read(m_DevicePort, &readBuffer, bufferSize);
    if (bytesRead <= 0) {
        std::cerr << "READ FAILURE\n"
                  << "Error:"
                  << getStrerror(errno) << ".\n";
        this->m_ConnectionStatus = ConnectionStatus::DeviceTimeout;
    }
    std::cerr << "Received response: " << readBuffer.data() << ".\n";
    return std::string { readBuffer.data() };
}

void BluetoothObdAccess::SetupDefaultTermios()
{
    // Set connection speed
    const int baudRate = B38400;
    // Set control flags: ignore modem control lines, enable reading
    m_Terminal.c_cflag = baudRate | CLOCAL | CREAD;
    // Ignore framing errors and parity errors
    m_Terminal.c_iflag = IGNPAR;
    // Clear output flags
    m_Terminal.c_oflag = 0;
    // Set non-canonical mode
    m_Terminal.c_lflag &= ~ICANON;
    // Set timeout of 1.0 seconds
    m_Terminal.c_cc[VTIME] = timeout;
    // Blocking read for 0.5 second between characters
    m_Terminal.c_cc[VMIN] = readBlockingInterval;
    // Flush device file contents
    tcflush(m_DevicePort, TCIOFLUSH);
    // Apply changes
    tcsetattr(m_DevicePort, TCSANOW, &m_Terminal);
}

void BluetoothObdAccess::SetDevice(Device device)
{
    if (device.GetConnectionType() != ConnectionType::Bluetooth) {
        throw std::logic_error(
            std::string("Invalid device set. Got" + std::to_string(static_cast<int16_t>(device.GetConnectionType())) + " expected Bluetooth").c_str());
    }
    this->m_Device = std::move(device);
}

bool BluetoothObdAccess::IsDeviceFileOk()
{
    return std::filesystem::exists(this->m_Device.GetDeviceFilePath());
}

bool BluetoothObdAccess::OpenConnection()
{
    // NOLINTNEXTLINE
    this->m_DevicePort = open(this->m_Device.GetDeviceFilePath().c_str(),
        O_RDWR | O_NOCTTY);

    // error occured
    return this->m_DevicePort == -1;
}

bool BluetoothObdAccess::Connect()
{
    std::clog << "Opening connection with " << this->m_Device.GetDeviceFilePath()
              << " " << this->m_Device.GetDescription() << ".\n";

    if (!IsDeviceFileOk()) {

        std::clog << "Device file" + this->m_Device.GetDeviceFilePath() << " not found.\n";

        m_ConnectionStatus = ConnectionStatus::DeviceNotFound;
        return false;
    }

    if(!OpenConnection())
    {
        this->m_ConnectionStatus = ConnectionStatus::Disconnected;
        std::clog << "Error:" << getStrerror(errno) << ".\n";
        return false;
    }
    std::clog << "OK.\n";
    this->m_ConnectionStatus = ConnectionStatus::Connected;
    return true;
}

} // namespace Obd
