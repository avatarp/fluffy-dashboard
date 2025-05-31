#include "elm327-engine.hpp"

Elm327Engine::Elm327Engine()
{
    m_commandRepository = std::make_shared<Elm327CommandRepository>();
    m_dataDecoder = std::make_shared<Elm327DataDecoder>();
    m_dataParser = std::make_shared<Elm327DataParser>();
}