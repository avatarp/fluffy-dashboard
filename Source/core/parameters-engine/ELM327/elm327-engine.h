#pragma once
#include "../parameters-engine.h"

class Elm327Engine : public ParametersEngine
{
public:
    Elm327Engine();
    virtual void SetupTermios();
    virtual void SetupTermios(termios interface);
    virtual bool OpenConnection();
    virtual bool CloseConnection();
};

