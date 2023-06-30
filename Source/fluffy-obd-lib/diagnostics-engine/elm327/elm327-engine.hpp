#pragma once
#include "../diagnostics-engine-base/diagnostics-engine.hpp"
#include "elm327-command-repository.hpp"
#include "elm327-data-filter.hpp"
#include "elm327-data-decoder.hpp"

class Elm327Engine : public ParametersEngine
{
public:
    Elm327Engine();
    virtual ~Elm327Engine();
    virtual void SetupTermios();
    virtual void SetupTermios(termios interface);
    virtual bool OpenConnection();
    virtual bool CloseConnection();
};

