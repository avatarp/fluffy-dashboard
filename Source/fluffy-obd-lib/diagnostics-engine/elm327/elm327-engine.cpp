#include "elm327-engine.hpp"

Elm327Engine::Elm327Engine()
{
    m_CommandRepository = std::make_unique<Elm327CommandRepository>();
    m_dataDecoder = std::make_unique<Elm327DataDecoder>();
    m_dataFilter = std::make_unique<Elm327DataParser>();
}

// void Elm327Engine::SetupTermios()
// {
//     // Clear rfcomm file
//     m_TerminalInterface.c_cflag = m_BaudRate | CS8 | CLOCAL | CREAD;
//     m_TerminalInterface.c_iflag = IGNPAR;
//     m_TerminalInterface.c_oflag = 0;
//     m_TerminalInterface.c_lflag &= ~ICANON; /* Set non-canonical mode */
//     m_TerminalInterface.c_cc[VTIME] = 5; // NOLINT
//     m_TerminalInterface.c_cc[VMIN] = 7; // NOLINT
//     tcflush(m_ConnectionHandle, TCIOFLUSH);
//     tcsetattr(m_ConnectionHandle, TCSANOW, &m_TerminalInterface);
// }

// void Elm327Engine::SetupTermios(termios interface)
// {
//     m_TerminalInterface = interface;
//     tcflush(m_ConnectionHandle, TCIOFLUSH);
//     tcsetattr(m_ConnectionHandle, TCSANOW, &m_TerminalInterface);
// }

bool Elm327Engine::OpenConnection()
{
    if (m_obdAccess) {
        return m_obdAccess->Connect();
    }
    std::clog << "No obd device set" << std::endl;
    return false;
}

bool Elm327Engine::CloseConnection()
{
    return m_obdAccess->CloseConnection();
}
