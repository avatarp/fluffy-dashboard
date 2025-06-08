#ifndef OBDRESPONSE_H
#define OBDRESPONSE_H

#include "obd-command-pid.hpp"
#include <bitset>
#include <iostream>
#include <string>
#include <utility>
#include <variant>

using Bitset_32 = std::bitset<32>;
using StringData = std::pair<std::string, std::string>;
using FloatData = std::pair<float, std::string>;
using FloatDataPair = std::pair<FloatData, FloatData>;

using DecodedData = std::variant<Bitset_32, FloatData, FloatDataPair, StringData>;

enum class DataType { empty,
    string,
    bitset,
    number,
    numberPair,
    dtc };

enum class ResponseState { invalid,
    raw,
    decoded };

struct RawResponse {
    std::string ecuId {};
    std::string commandId {};
    uint8_t length { 0 };
    std::string data {};
};

struct Response {

    ResponseState state { ResponseState::invalid };
    RawResponse raw {};

    ObdCommandPid commandPid {};
    DataType dataType { DataType::empty };
    DecodedData decodedData {};

    friend std::ostream& operator<<(std::ostream& ost, const Response& resp);
};

#endif // OBDRESPONSE_H
