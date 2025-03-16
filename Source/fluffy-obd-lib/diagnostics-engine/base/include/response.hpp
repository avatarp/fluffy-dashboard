#ifndef OBDRESPONSE_H
#define OBDRESPONSE_H

#include "obd-command-pid.hpp"
#include <bitset>
#include <iostream>
#include <string>
#include <utility>

using bitset_32 = std::bitset<32>;
using stringData = std::pair<std::string, std::string>;
using floatData = std::pair<float, std::string>;

enum class DataType { empty,
    string,
    bitset,
    number,
    numberPair,
    dtc };

enum class ResponseState { invalid,
    raw,
    decoded };

struct Response {
    ResponseState state { ResponseState::invalid };
    std::string m_rawEcuId {};
    std::string m_rawCommandId {};
    uint8_t m_rawLength { 0 };
    std::string m_rawData {};

    ObdCommandPid commandPid {};
    DataType m_dataType { DataType::empty };
    bitset_32 m_dataBitset {};
    floatData m_dataFloat1 {};
    floatData m_dataFloat2 {};
    stringData m_dataString {};

    friend std::ostream& operator<<(std::ostream& ost, const Response& resp);
};

#endif // OBDRESPONSE_H
