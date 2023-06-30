#ifndef OBDRESPONSE_H
#define OBDRESPONSE_H
#include <string>
#include <bitset>
#include <utility>
#include <iostream>

enum class DataType
{
    empty,
    string,
    bitset,
    number,
    numberPair,
    dtc
};


struct RawResponse
{
    std::string m_ecuId;
    std::string m_commandId;
    uint8_t m_lenght{0};
    std::string m_data;
};

struct Response
{
    RawResponse m_rawResponse;
    DataType m_dataType;
    std::bitset<32> m_dataBitset;
    std::pair<float, std::string> m_floatData1;
    std::pair<float, std::string> m_floatData2;
    std::pair<std::string, std::string> m_stringData;

    Response();
    Response(const RawResponse &rawResponse,
             const std::bitset<32> &bitset);
    Response(const RawResponse &rawResponse,
             const std::string &data, const std::string &type);
    Response(const RawResponse &rawResponse,
             float data, const std::string &unit);
    Response(const RawResponse &rawResponse,
             float data1, const std::string &unit1,
             float data2, const std::string &unit2);
    friend std::ostream& operator<<(std::ostream& os, const Response& resp);
};

#endif //OBDRESPONSE_H
