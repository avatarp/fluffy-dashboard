#include "response.hpp"
#include <regex>
#include <string>

class DataParser {
public:
    virtual ~DataParser() { }
    virtual RawResponse ParseResponse(std::string data, const size_t dataBytesCount, const std::string& commandPid)
        = 0;
};