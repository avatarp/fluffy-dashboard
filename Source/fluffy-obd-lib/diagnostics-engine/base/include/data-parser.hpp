#ifndef DATA_FILTERS_HPP_
#define DATA_FILTERS_HPP_

#include "data-decoder.hpp"
#include "obd-command-pid.hpp"
#include "response.hpp"
#include <regex>
#include <string>

class DataParser {
protected:
    std::shared_ptr<DataDecoder> m_decoder {};

public:
    virtual ~DataParser() { }
    virtual Response ParseResponse(const std::string& command, std::string response, ObdCommandPid pid) = 0;
};

#endif // DATA_FILTERS_HPP_