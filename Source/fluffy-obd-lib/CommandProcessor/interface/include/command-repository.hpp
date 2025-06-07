#ifndef COMMAND_REPOSITORY_HPP_
#define COMMAND_REPOSITORY_HPP_

#include <string>

#include "obd-command-pid.hpp"

class CommandRepository {
public:
    CommandRepository() = default;
    virtual ~CommandRepository() = default;
    virtual std::string getCommandByPid(ObdCommandPid pid) = 0;
};

#endif // COMMAND_REPOSITORY_HPP_