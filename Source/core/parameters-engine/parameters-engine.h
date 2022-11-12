#pragma once
#include <memory>
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
#include "response.h"

class ParametersEngine
{
    const int BUFFER_SIZE = 256;
    static constexpr int m_readSleepTime{500 * 1000};//ms
protected:
    termios m_TerminalInterface;
    Obd::Device m_SerialDevice;
    unsigned m_BaudRate;
    int m_ConnectionHandle;
    std::unique_ptr<DataDecodingHandler> m_dataDecoder;
    std::unique_ptr<DataParser> m_dataFilter;
    std::unique_ptr<CommandRepository> m_CommandRepository;
    virtual bool SendCommand(const std::string &command);
    virtual std::string ReadResponse();
public:
    ParametersEngine() = default;
    virtual ~ParametersEngine() = default;
    void SetSerialDevice(Obd::Device device);
    virtual void SetupTermios() = 0;
    virtual void SetupTermios(termios interface) = 0;
    virtual bool OpenConnection() = 0;
    virtual bool CloseConnection() = 0;
    Response GetCommandResponse(ObdCommandPid pid);

};

