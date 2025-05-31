#ifndef DIAGNOSTICS_ENGINE_HPP_
#define DIAGNOSTICS_ENGINE_HPP_

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

#include "command-repository.hpp"
#include "data-decoder.hpp"
#include "data-parser.hpp"
#include "device.hpp"
#include "obd-access.hpp"
#include "obd-command-pid.hpp"
#include "response.hpp"

class ICommandProcessor {
    static constexpr int BUFFER_SIZE = 256;
    static constexpr int m_readSleepTime { 500 * 1000 }; // ms
protected:
    std::shared_ptr<Obd::ObdAccess> m_obdAccess {};
    std::shared_ptr<DataDecoder> m_dataDecoder {};
    std::shared_ptr<DataParser> m_dataParser {};
    std::shared_ptr<CommandRepository> m_commandRepository {};
    virtual bool SendCommand(const std::string& command);
    virtual std::string ReadResponse();

public:
    ICommandProcessor() = default;
    virtual ~ICommandProcessor() = default;
    void SetSerialDevice(Obd::Device device);
    void SetObdAccess(std::unique_ptr<Obd::ObdAccess> obdAccess);
    virtual bool OpenConnection();
    virtual bool Disconnect();
    Response GetCommandResponse(ObdCommandPid pid);
};

#endif // DIAGNOSTICS_ENGINE_HPP_
