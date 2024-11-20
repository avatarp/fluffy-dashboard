#ifndef ELM327_DATA_PARSER_HPP_
#define ELM327_DATA_PARSER_HPP_

#include "data-parser.hpp"
#include "elm327-data-decoder.hpp"
#include <regex>
#include <string>

class Elm327DataParser : public DataParser {
private:
    void processResponse(Response& parsedResponse, ObdCommandPid pid);

public:
    Elm327DataParser();
    virtual Response ParseResponse(const std::string& command, std::string response, ObdCommandPid pid) override;
    static std::size_t getExpectedResponseSizeByPid(ObdCommandPid pid);
};

#endif // ELM327_DATA_PARSER_HPP_