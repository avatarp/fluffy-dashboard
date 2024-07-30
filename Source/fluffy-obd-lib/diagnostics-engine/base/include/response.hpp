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

struct RawResponse {
    std::string m_ecuId {};
    std::string m_commandId {};
    uint8_t m_length { 0 };
    std::string m_data {};
};

using bitset_32 = std::bitset<32>;
struct Response {
    RawResponse m_rawResponse {};
    DataType m_dataType { DataType::empty };
    bitset_32 m_dataBitset {};
    std::pair<float, std::string> m_floatData1 {};
    std::pair<float, std::string> m_floatData2 {};
    std::pair<std::string, std::string> m_stringData {};

    Response() = default;
    Response(RawResponse rawResponse, bitset_32 bitset);
    Response(RawResponse rawResponse, std::string data, std::string type);
    Response(RawResponse rawResponse, float data, std::string unit);
    Response(
        RawResponse rawResponse, float data1, std::string unit1, float data2, std::string unit2);
    friend std::ostream& operator<<(std::ostream& ost, const Response& resp);
};

#endif // OBDRESPONSE_H
