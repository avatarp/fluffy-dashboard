#include "response.h"

Response::Response(){
    m_dataType = DataType::empty;
}

Response::Response(const RawResponse &rawResponse, const std::bitset<32> &bitset)
{
    this->m_rawResponse = rawResponse;
    this->m_dataType = DataType::bitset;
    this->m_dataBitset = bitset;
}

Response::Response(const RawResponse &rawResponse,
                   const std::string &data, const std::string &type)
{
    m_rawResponse = rawResponse;
    this->m_dataType = DataType::string;
    m_stringData.first = data;
    m_stringData.second = type;
}

Response::Response(const RawResponse &rawResponse,
                   float data, const std::string &unit)
{
    m_rawResponse = rawResponse;
    this->m_dataType = DataType::number;
    m_floatData1.first = data;
    m_floatData1.second = unit;
}

Response::Response(const RawResponse &rawResponse,
                   float data1, const std::string &unit1,
                   float data2, const std::string &unit2)
{
    m_rawResponse = rawResponse;
    this->m_dataType = DataType::numberPair;
    this->m_floatData1.first = data1;
    this->m_floatData1.second = unit1;
    this->m_floatData2.first = data2;
    this->m_floatData2.second = unit2;
}

std::ostream& operator<<(std::ostream& os, const Response& resp)
{
switch (resp.m_dataType) {
case DataType::string:
    os << "string: "
       << resp.m_stringData.first << ", "
       << resp.m_stringData.second << '\n';
    break;
case DataType::number:
    os << "float: "
       << resp.m_floatData1.first << ", "
       << resp.m_floatData1.second << '\n';
    break;
case DataType::numberPair:
    os << "float pair: "
       << resp.m_floatData1.first << ", "
       << resp.m_floatData1.second << '\n'
       << resp.m_floatData2.first << ", "
       << resp.m_floatData2.second << '\n';
    break;
case DataType::dtc:
    os << "dtc string: "
       << resp.m_stringData.first << ", "
       << resp.m_stringData.second << '\n';
    break;
case DataType::bitset:
    os << "bitset: " << resp.m_dataBitset <<'\n';
    break;
default:
    os << "Empty response" <<'\n';
    break;
}
return os;
}
