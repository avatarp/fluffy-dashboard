#ifndef OBDRESPONSE_H
#define OBDRESPONSE_H
#include <bitset>
#include <iostream>
#include <string>
#include <utility>

enum class DataType { empty,
    string,
    bitset,
    number,
    numberPair,
    dtc };

using bitset_32 = std::bitset<32>;
using stringData = std::pair<std::string, std::string>;
using floatData = std::pair<float, std::string>;

struct Response {
    std::string m_rawEcuId {};
    std::string m_rawCommandId {};
    uint8_t m_rawLength { 0 };
    std::string m_rawData {};
    DataType m_dataType { DataType::empty };
    bitset_32 m_dataBitset {};
    floatData m_dataFloat1 {};
    floatData m_dataFloat2 {};
    stringData m_dataString {};

    friend std::ostream& operator<<(std::ostream& ost, const Response& resp);
};

#endif // OBDRESPONSE_H
