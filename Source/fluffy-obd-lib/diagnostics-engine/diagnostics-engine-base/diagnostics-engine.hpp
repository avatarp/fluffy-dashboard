#pragma once
#include <bitset>
#include <errno.h>
#include <exception>
#include <fcntl.h>
#include <iostream>
#include <memory>
#include <optional>
#include <string.h>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <variant>

#include "../../obd-access/device.hpp"
#include "../../obd-access/logging.hpp"
#include "command-repository.hpp"
#include "data-decoding-handler.hpp"
#include "data-filters.hpp"
#include "dtc-handler.hpp"
#include "obd-command-pid.hpp"
#include "response.hpp"

class ParametersEngine {
    static constexpr int BUFFER_SIZE = 256;
    static constexpr int m_readSleepTime { 500 * 1000 }; // ms
protected:
    termios m_TerminalInterface;
    Obd::Device m_SerialDevice;
    unsigned m_BaudRate;
    int m_ConnectionHandle;
    std::unique_ptr<DataDecodingHandler> m_dataDecoder;
    std::unique_ptr<DataParser> m_dataFilter;
    std::unique_ptr<CommandRepository> m_CommandRepository;
    virtual bool SendCommand(const std::string& command);
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
