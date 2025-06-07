#ifndef ELM327_COMMAND_REPOSITORY_HPP_
#define ELM327_COMMAND_REPOSITORY_HPP_

#include "command-repository.hpp"
#include <unordered_map>

class Elm327CommandRepository : public CommandRepository {
    static const std::unordered_map<ObdCommandPid, std::string>& getCommandMap();

public:
    Elm327CommandRepository() = default;
    ~Elm327CommandRepository() = default;
    virtual std::string getCommandByPid(ObdCommandPid pid);
};

#endif // ELM327_COMMAND_REPOSITORY_HPP_