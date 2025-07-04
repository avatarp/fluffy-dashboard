#ifndef ELM327_COMMAND_PROCESSOR_HPP_
#define ELM327_COMMAND_PROCESSOR_HPP_

#include "ICommandProcessor.hpp"
#include "elm327-command-repository.hpp"
#include "elm327-data-decoder.hpp"
#include "elm327-data-parser.hpp"
#include "elm327-dtc-handler.hpp"

class Elm327CommandProcessor : public ICommandProcessor {

    virtual Response RetrieveMultiFrameResponse(const std::string& command, std::smatch& match, ObdCommandPid pid) override;
    static uint8_t GetExpectedFramesCount(ObdCommandPid pid, uint8_t dataItemsCount);

public:
    Elm327CommandProcessor()
        : ICommandProcessor(
            std::make_shared<Elm327DataDecoder>(),
            std::make_shared<Elm327DataParser>(),
            std::make_shared<Elm327CommandRepository>(),
            std::make_shared<Elm327DtcHandler>())
    {
    }
    virtual ~Elm327CommandProcessor() = default;

    Response GetCommandResponse(ObdCommandPid pid) override;
};

#endif // ELM327_COMMAND_PROCESSOR_HPP_