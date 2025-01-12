#include "bluetooth-obd-access.hpp"
#include <thread>

namespace Obd {

bool BluetoothObdAccess::Write(const std::string& command)
{
    if (this->GetConnectionStatus() != ConnectionStatus::Connected) {
        std::cerr << "device not connected.\n";
        return false;
    }

    errno = 0;
    std::clog << "Writing command " + command << "\n";
    ssize_t bytesWritten = write(m_DeviceFileDescriptor, command.c_str(), command.length());

    if (bytesWritten == -1) {
        constexpr size_t errBufferSize = 1024;
        std::array<char, errBufferSize> errBuffer {};
        std::cerr << "WRITE FAILURE\n"
                  << "Error:" << strerror_r(errno, errBuffer.data(), errBufferSize) << "\n";
        errno = 0;
        m_ConnectionStatus = ConnectionStatus::ConnectionLost;
        return false;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(afterWriteSleepTime));

    if (command.size() != static_cast<std::size_t>(bytesWritten)) {
        std::cerr << "Error! Written " << bytesWritten << " bytes. Expected "
                  << command.length() << ".\n";
        return false;
    }

    std::clog << "Written " << bytesWritten << " bytes successfully.\n";
    return true;
}

std::string BluetoothObdAccess::Read()
{
    errno = 0;
    std::array<char, bufferSize> readBuffer {};
    ssize_t bytesRead = read(m_DeviceFileDescriptor, &readBuffer, bufferSize);
    if (bytesRead <= 0) {
        constexpr size_t errBufferSize = 1024;
        std::array<char, errBufferSize> errBuffer {};
        std::cerr << "READ FAILURE\n"
                  << "Error:"
                  << strerror_r(errno, errBuffer.data(), errBufferSize) << ".\n";
        errno = 0;
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
        constexpr size_t errBufferSize = 1024;
        std::array<char, errBufferSize> errBuffer {};
        std::cerr << "Error applying default termios settings\n"
                  << "Error:"
                  << strerror_r(errno, errBuffer.data(), errBufferSize) << ".\n";
        errno = 0;
        return false;
    }
    return true;
#pragma GCC diagnostic pop
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
    return std::filesystem::exists(m_Device.GetDeviceFilePath());
}

bool BluetoothObdAccess::OpenConnection()
{
    // NOLINTNEXTLINE
    m_DeviceFileDescriptor = open(m_Device.GetDeviceFilePath().c_str(), O_RDWR | O_NOCTTY);
    if (m_DeviceFileDescriptor == -1) {
        constexpr size_t errBufferSize = 1024;
        std::array<char, errBufferSize> errBuffer {};
        std::cerr << "Open failure\n"
                  << "Error:" << strerror_r(errno, errBuffer.data(), errBufferSize) << "\n";
        errno = 0;
    }
    return true;
}

bool BluetoothObdAccess::Connect()
{
    std::clog << "Opening connection with " << this->m_Device.GetDeviceFilePath()
              << " " << this->m_Device.GetDescription() << ".\n";

    if (!IsDeviceFileOk()) {

        std::cerr << "Device file" + this->m_Device.GetDeviceFilePath() << " not found!\n";

        m_ConnectionStatus = ConnectionStatus::DeviceNotFound;
        return false;
    }

    if (!OpenConnection()) {
        this->m_ConnectionStatus = ConnectionStatus::Disconnected;
        constexpr size_t errBufferSize = 1024;
        std::array<char, errBufferSize> errBuffer {};
        std::cerr << "Error:" << strerror_r(errno, errBuffer.data(), errBufferSize) << "\n";
        return false;
    }

    if (ApplyDefaultConnectionSettings()) {
        std::clog << "Default connection settings applied\n";
    } else {
        std::cerr << "Failed to apply default connection settings\n";
        return false;
    }

    std::clog << "Opening connection successful\n";
    this->m_ConnectionStatus = ConnectionStatus::Connected;
    return true;
}

} // namespace Obd
