#ifndef DATA_FILTERS_HPP_
#define DATA_FILTERS_HPP_

#include "response.hpp"
#include <regex>
#include <string>

class DataParser {
public:
    virtual ~DataParser() { }
    virtual RawResponse ParseResponse(std::string data, const size_t& dataBytesCount, const std::string& commandPid)
        = 0;
};

#endif // DATA_FILTERS_HPP_