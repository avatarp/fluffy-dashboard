#include "elm327-engine.hpp"

Elm327Engine::Elm327Engine()
    : ICommandProcessor(
        std::make_shared<Elm327DataDecoder>(),
        std::make_shared<Elm327DataParser>(),
        std::make_shared<Elm327CommandRepository>())
{
}