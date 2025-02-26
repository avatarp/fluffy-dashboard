#include "bluetooth-obd-access.hpp"
#include <thread>

namespace Obd {

bool BluetoothObdAccess::Write(const std::string& command)
{
    if (this->GetConnectionStatus() != ConnectionStatus::Connected) {
        spdlog::error("Device not connected.");
        return false;
    }

    errno = 0;
    spdlog::info("Writing command: {}", command);
    ssize_t bytesWritten = write(m_DeviceFileDescriptor, command.c_str(), command.length());

    if (bytesWritten == -1) {
        logErrno("WRITE FAILURE\n Error:");
        m_ConnectionStatus = ConnectionStatus::ConnectionLost;
        return false;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(afterWriteSleepTime));

    if (command.size() != static_cast<std::size_t>(bytesWritten)) {
        spdlog::error("Error! Written {} bytes. Expected {}.", bytesWritten, command.length());
        return false;
    }
    spdlog::info("Written {} bytes successfully.", bytesWritten);
    return true;
}

std::string BluetoothObdAccess::Read()
{
    errno = 0;
    std::array<char, bufferSize> readBuffer {};
    ssize_t bytesRead = read(m_DeviceFileDescriptor, &readBuffer, bufferSize);
    if (bytesRead <= 0) {
        logErrno("READ FAILURE\n Error:");
        this->m_ConnectionStatus = ConnectionStatus::DeviceTimeout;
    }
    return std::string { readBuffer.data() };
}

bool BluetoothObdAccess::ApplyDefaultConnectionSettings()
{
// disable false positive Wsign-conversion warnings
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
    errno = 0;
    tcgetattr(m_DeviceFileDescriptor, &m_Terminal);

    // Connection speed
    constexpr int baudRate { B38400 }; // B9600 if pin6 = 0V
    cfsetispeed(&m_Terminal, baudRate);
    cfsetospeed(&m_Terminal, baudRate);

    // Control options
    m_Terminal.c_cflag |= (CLOCAL | CREAD); // ignore modem control lines, enable reading
    // 8N1 - 8 data bits, no parity bit, 1 stop bit
    m_Terminal.c_cflag &= ~CSIZE; // Clears the mask for setting the data size
    m_Terminal.c_cflag |= CS8; // Set the data bits = 8
    m_Terminal.c_cflag &= ~PARENB; // no parity bit
    m_Terminal.c_cflag &= ~CSTOPB; // use 1 Stop bit (disable 2 stop bits)

    // Local mode options
    // Set raw mode, no echo, no signals
    m_Terminal.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    // Input options
    m_Terminal.c_iflag &= ~(INPCK | ISTRIP); // Disable checking and stripping of parity bits
    m_Terminal.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable software flow control

    // Output options
    m_Terminal.c_oflag &= ~OPOST; // Disable output processing

    // Control characters
    m_Terminal.c_cc[VMIN] = 0; // minimum number of characters to read
    constexpr unsigned char timeout = 10;
    m_Terminal.c_cc[VTIME] = timeout; // timeout for incoming data in 0.1s

    // Flush buffers and apply options
    tcsetattr(m_DeviceFileDescriptor, TCSAFLUSH, &m_Terminal);

    if (errno != 0) {
        logErrno("Error applying default termios settings\n Error:");
        return false;
    }
    return true;
#pragma GCC diagnostic pop
}

void BluetoothObdAccess::SetDevice(Device device)
{
    if (device.m_ConnectionType != ConnectionType::Bluetooth) {
        throw std::logic_error(
            std::string("Invalid device set. Got" + std::to_string(static_cast<int16_t>(device.m_ConnectionType)) + " expected Bluetooth").c_str());
    }
    this->m_Device = std::move(device);
}

bool BluetoothObdAccess::IsDeviceFileOk()
{
    return std::filesystem::exists(m_Device.m_DeviceFilePath);
}

bool BluetoothObdAccess::OpenConnection()
{
    // NOLINTNEXTLINE
    m_DeviceFileDescriptor = open(m_Device.m_DeviceFilePath.c_str(), O_RDWR | O_NOCTTY);
    if (m_DeviceFileDescriptor == -1) {
        logErrno("Open failure\n Error:");
        return false;
    }
    return true;
}

bool BluetoothObdAccess::Connect()
{
    spdlog::info("Opening connection with {} {}.", this->m_Device.m_DeviceFilePath, this->m_Device.m_Description);

    if (!IsDeviceFileOk()) {
        spdlog::error("Device file {} not found!", this->m_Device.m_DeviceFilePath);
        m_ConnectionStatus = ConnectionStatus::DeviceNotFound;
        return false;
    }

    if (!OpenConnection()) {
        this->m_ConnectionStatus = ConnectionStatus::Disconnected;
        logErrno("Failed to open connection\n Error:");
        return false;
    }

    if (ApplyDefaultConnectionSettings()) {
        spdlog::debug("Default connection settings applied");
    } else {
        spdlog::error("Failed to apply default connection settings");
        return false;
    }
    spdlog::info("Opening connection successful");
    this->m_ConnectionStatus = ConnectionStatus::Connected;
    return true;
}

} // namespace Obd
