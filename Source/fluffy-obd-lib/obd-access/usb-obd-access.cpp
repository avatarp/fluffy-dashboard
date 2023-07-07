#include "usb-obd-access.hpp"

namespace Obd {

bool UsbObdAccess::Write(const std::string &command)
{
    if(this->GetConnectionStatus()!=ConnectionStatus::Connected){
        std::clog<<"device not connected.\n";
        return false;
    }

    std::clog << "Writing command " + command << ".\n";
    ssize_t bytesWritten = write(this->m_DevicePort,
                             command.c_str(),
                             command.length());

    if(bytesWritten==-1)
    {
        std::clog<< "WRITE FAILURE\n"
                 << "Error:"
                 << getStrerror(errno)<<".\n";
        m_ConnectionStatus=ConnectionStatus::ConnectionLost;
        return false;
    }

    if (command.size() == bytesWritten)
    {
        std::clog << "Written "
                  << bytesWritten
                  << " bytes succesfully.\n";
        return true;
    }

    std::clog << "Written "
              << bytesWritten
              << " bytes. Expected "
              << command.length() << ".\n";

    return false;
}

std::string UsbObdAccess::Read()
{
    std::array<char, bufferSize> readBuffer{};
    ssize_t bytesRead = read(m_DevicePort, &readBuffer, bufferSize);
    if (bytesRead <= 0)
    {
        std::clog << "READ FAILURE\n"
                  << "Error:"
                  << getStrerror(errno) << ".\n";
        this->m_ConnectionStatus = ConnectionStatus::DeviceTimeout;
    }
    std::clog << "Received response: "
              << readBuffer.data() << ".\n";
    return std::string{readBuffer.data()};
}

void UsbObdAccess::SetupDefaultTermios()
{
    //Set control flags:
    //connection speed, ignore modem control lines, enable reading
    const int baudRate=B38400;
    m_Terminal.c_cflag = baudRate | CLOCAL | CREAD;
    //Ignore framing errors and parity errors
    m_Terminal.c_iflag = IGNPAR;
    //Clear output flags
    m_Terminal.c_oflag = 0;
    //Set non-canonical mode
    m_Terminal.c_lflag &= ~ICANON;
    //Set timeout of 0.5 seconds
    m_Terminal.c_cc[VTIME] = timeout;
    //Blocking read for 0.3 second between characters
    m_Terminal.c_cc[VMIN] = readBlockingInterval;
    //Flush device file contents
    tcflush(m_DevicePort, TCIOFLUSH);
    //Apply changes
    tcsetattr(m_DevicePort,TCSANOW,&m_Terminal);

}

void UsbObdAccess::SetDevice(Device device)
{
    if(device.GetConnectionType() != ConnectionType::Usb)
    {
        throw std::logic_error(std::string(
                                   "Invalid device set. Got"
                                   + std::to_string(
                                       (int)device.GetConnectionType())
                                   + " expected 1").c_str());
    }
    this->m_Device = std::move(device);
}

bool UsbObdAccess::Connect()
{
    std::clog<<"Opening connection with "
            << this->m_Device.GetDeviceFilePath()
            << " " << this->m_Device.GetDescription()
            <<".\n";

    if(!std::filesystem::exists(this->m_Device.GetDeviceFilePath())){

        std::clog<<"Device file" + this->m_Device.GetDeviceFilePath() <<
                   " not found.\n";

        m_ConnectionStatus=ConnectionStatus::DeviceNotFound;
        return false;
    }
    
    // NOLINTNEXTLINE
    this->m_DevicePort = open(this->m_Device.GetDeviceFilePath().c_str(),
                              O_RDWR | O_NOCTTY );

    if (this->m_DevicePort == -1)//error occured
    {
        this->m_ConnectionStatus=ConnectionStatus::Disconnected;
        std::clog<<"Error:"<<getStrerror(errno)<<".\n";
        return false;
    }
    std::clog<<"OK.\n";
    this->m_ConnectionStatus=ConnectionStatus::Connected;
    return true;
}

} // namespace Obd
