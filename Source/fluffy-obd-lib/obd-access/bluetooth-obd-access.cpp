#include "bluetooth-obd-access.hpp"

namespace Obd {

bool BluetoothObdAccess::Write(const std::string &command)
{
    if(this->GetConnectionStatus()!=ConnectionStatus::Connected){
        std::clog<<"device not connected.\n";
        return false;
    }

    std::clog << "Writing command " + command << ".\n";
    int bytesWritten = write(
                this->m_DevicePort, command.c_str(), command.length());

    if(bytesWritten==-1)
    {
        std::clog<< "WRITE FAILURE\n" << "Error:" << strerror(errno)<<".\n";
        m_ConnectionStatus=ConnectionStatus::ConnectionLost;
        return false;
    }
    else
    {
        if (command.size() == bytesWritten)
        {
            std::clog<<"Written " << bytesWritten << " bytes succesfully.\n";
            return true;
        }
        else
        {
            std::clog<<"Written " << bytesWritten << " bytes. Expected "
                    << command.length() << ".\n";
        }
        return false;
    }
}

std::string BluetoothObdAccess::Read()
{
    char readBuffer[bufferSize]{};
    memset(&readBuffer, '\0', sizeof(readBuffer));
    int bytesRead = read(m_DevicePort, &readBuffer, bufferSize);
    if(bytesRead <= 0)
    {
        std::clog<<"READ FAILURE\n"<<"Error:"
                <<strerror(errno)<<".\n";
        this->m_ConnectionStatus=ConnectionStatus::DeviceTimeout;
    }
    std::clog<<"Received response: " << readBuffer << ".\n";
    return std::string(readBuffer);
}

void BluetoothObdAccess::SetupDefaultTermios()
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
    //Set timeout of 1.0 seconds
    m_Terminal.c_cc[VTIME] = 10;
    //Blocking read for 0.5 second between characters
    m_Terminal.c_cc[VMIN] = 5;
    //Flush device file contents
    tcflush(m_DevicePort, TCIOFLUSH);
    //Apply changes
    tcsetattr(m_DevicePort,TCSANOW,&m_Terminal);

}

BluetoothObdAccess::~BluetoothObdAccess(){}

void BluetoothObdAccess::SetDevice(Device device)
{
    if(device.GetConnectionType() != ConnectionType::Bluetooth)
        throw std::logic_error(
                std::string("Invalid device set. Got"
                            + std::to_string((int)device.GetConnectionType())
                            + " expected Bluetooth").c_str()
                );
    this->m_Device = std::move(device);
}

bool BluetoothObdAccess::Connect()
{
    std::clog<<"Opening connection with " << this->m_Device.GetDeviceFilePath()
            << " " << this->m_Device.GetDescription() <<".\n";

    if(!std::filesystem::exists(this->m_Device.GetDeviceFilePath())){

        std::clog<<"Device file" + this->m_Device.GetDeviceFilePath() <<
                   " not found.\n";

        m_ConnectionStatus=ConnectionStatus::DeviceNotFound;
        return false;
    }

    this->m_DevicePort = open(this->m_Device.GetDeviceFilePath().c_str(),
                              O_RDWR | O_NOCTTY );

    if (this->m_DevicePort == -1)//error occured
    {
        this->m_ConnectionStatus=ConnectionStatus::Disconnected;
        std::clog<<"Error:"<<strerror(errno)<<".\n";
        return false;
    }
    std::clog<<"OK.\n";
    this->m_ConnectionStatus=ConnectionStatus::Connected;
    return true;
}

}
