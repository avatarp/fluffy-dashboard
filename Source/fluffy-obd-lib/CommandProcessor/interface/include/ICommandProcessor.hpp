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

    virtual Response RetrieveMultiFrameResponse(const std::string& command, std::smatch& match, ObdCommandPid pid) = 0;

public:
    ICommandProcessor() = default;

    ICommandProcessor(
        std::shared_ptr<DataDecoder> dataDecoder,
        std::shared_ptr<DataParser> dataParser,
        std::shared_ptr<CommandRepository> commandRepository)
        : m_dataDecoder(std::move(dataDecoder))
        , m_dataParser(std::move(dataParser))
        , m_commandRepository(std::move(commandRepository))
    {
    }

    virtual ~ICommandProcessor() = default;

    void SetObdAccess(std::shared_ptr<Obd::ObdAccess> obdAccess);
    std::shared_ptr<Obd::ObdAccess> GetObdAccess() const;

    virtual bool OpenConnection();
    virtual bool Disconnect();
    virtual Response GetCommandResponse(ObdCommandPid pid) = 0;
};

#endif // DIAGNOSTICS_ENGINE_HPP_
