#pragma once
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>
#include <fcntl.h>
#include <string>
#include <string.h>
#include <variant>
#include <bitset>
#include <exception>
#include <optional>
#include "data-decoding-handler.h"
#include "dtc-handler.h"
#include "command-repository.h"
#include "data-filters.h"
#include "../obd-access/device.h"
#include "obd-command-pid.h"

class ParametersEngine
{
    const int BUFFER_SIZE = 256;
protected:
    termios m_TerminalInterface;
    Obd::Device m_SerialDevice;
    unsigned m_BaudRate;
    int m_ConnectionHandle;
    //DataDecodingHandler *m_DataObtainer;
    DataFilters *m_DataFilter;
    DtcHandler *m_DtcHandler;
    //CommandRepository *m_CommandRepository;
    virtual bool SendCommand(const std::string &command);
    virtual std::string ReadResponse();
public:

    ParametersEngine();
    void SetSerialDevice(Obd::Device device);
    virtual void SetupTermios() = 0;
    virtual void SetupTermios(termios interface) = 0;
    virtual bool OpenConnection() = 0;
    virtual bool CloseConnection() = 0;
    std::variant<
        std::optional<float>,
        std::optional<std::pair<std::optional<float>, std::optional<float>>>,
        std::optional<std::bitset<32>>,
        std::optional<std::string>
    > GetCommandResponse(ObdCommandPid pid);

};

