#pragma once
#include "../parameters-engine.h"
#include "elm327-command-repository.h"
#include "elm327-data-filter.h"
#include "elm327-data-decoder.h"

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

