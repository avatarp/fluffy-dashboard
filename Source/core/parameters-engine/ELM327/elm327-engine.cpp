#include "elm327-engine.h"

Elm327Engine::Elm327Engine()
{
    m_CommandRepository = std::unique_ptr<CommandRepository>(new Elm327CommandRepository);
    m_dataDecoder = std::unique_ptr<DataDecodingHandler>(new Elm327DataDecoder);
    m_dataFilter = std::unique_ptr<DataParser>(new Elm327DataParser);
    m_BaudRate = B38400;
}

Elm327Engine::~Elm327Engine()
{

}

void Elm327Engine::SetupTermios()
{
    //Clear rfcomm file
    bzero(&m_SerialDevice, sizeof(m_ConnectionHandle));
    m_TerminalInterface.c_cflag = m_BaudRate | CS8 | CLOCAL | CREAD;
    m_TerminalInterface.c_iflag = IGNPAR;
    m_TerminalInterface.c_oflag = 0;
    m_TerminalInterface.c_lflag &= ~ICANON;     /* Set non-canonical mode */
    m_TerminalInterface.c_cc[VTIME]    = 5;
    m_TerminalInterface.c_cc[VMIN]     = 7;
    tcflush(m_ConnectionHandle, TCIOFLUSH);
    tcsetattr(m_ConnectionHandle, TCSANOW, &m_TerminalInterface);
}

void Elm327Engine::SetupTermios(termios interface)
{
    m_TerminalInterface = interface;
    bzero(&m_SerialDevice, sizeof(m_ConnectionHandle));
    tcflush(m_ConnectionHandle, TCIOFLUSH);
    tcsetattr(m_ConnectionHandle, TCSANOW, &m_TerminalInterface);
}

bool Elm327Engine::OpenConnection()
{
    m_ConnectionHandle = open(m_SerialDevice.GetDeviceFilePath().c_str(),
                              O_RDWR | O_NOCTTY );
    if (m_ConnectionHandle == -1)
        return false;

    return true;
}

bool Elm327Engine::CloseConnection()
{
    m_TerminalInterface.c_cflag = B0;

    try {
        if(m_ConnectionHandle > 0)
            close(m_ConnectionHandle);
    }
    catch(...){
        return false;
    }

    return true;
}

