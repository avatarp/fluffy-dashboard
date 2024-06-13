#include "elm327-engine.hpp"

Elm327Engine::Elm327Engine()
{
    m_CommandRepository = std::make_unique<Elm327CommandRepository>();
    m_dataDecoder = std::make_unique<Elm327DataDecoder>();
    m_dataFilter = std::make_unique<Elm327DataParser>();
}

bool Elm327Engine::OpenConnection()
{
    if (m_obdAccess) {
        return m_obdAccess->Connect();
    }
    std::clog << "No obd device set" << std::endl;
    return false;
}

bool Elm327Engine::CloseConnection()
{
    return m_obdAccess->CloseConnection();
}
