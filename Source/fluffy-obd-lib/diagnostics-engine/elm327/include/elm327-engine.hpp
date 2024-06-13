#ifndef ELM327_ENGINE_HPP_
#define ELM327_ENGINE_HPP_

#include "diagnostics-engine.hpp"
#include "elm327-command-repository.hpp"
#include "elm327-data-decoder.hpp"
#include "elm327-data-parser.hpp"

class Elm327Engine : public ParametersEngine {
public:
    Elm327Engine();
    virtual ~Elm327Engine() = default;
    virtual bool OpenConnection();
    virtual bool CloseConnection();
};

#endif // ELM327_ENGINE_HPP_