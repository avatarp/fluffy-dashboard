#ifndef ELM327_ENGINE_HPP_
#define ELM327_ENGINE_HPP_

#include "ICommandProcessor.hpp"
#include "elm327-command-repository.hpp"
#include "elm327-data-decoder.hpp"
#include "elm327-data-parser.hpp"

class Elm327Engine : public ICommandProcessor {
public:
    Elm327Engine();
    virtual ~Elm327Engine() = default;
};

#endif // ELM327_ENGINE_HPP_