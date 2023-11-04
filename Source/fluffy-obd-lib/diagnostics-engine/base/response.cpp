#include "response.hpp"

Response::Response(RawResponse rawResponse, bitset_4B bitset)
    : m_rawResponse(std::move(rawResponse))
    , m_dataType(DataType::bitset)
    , m_dataBitset(bitset)
{
}

Response::Response(RawResponse rawResponse, std::string data, std::string type)
    : m_rawResponse(std::move(rawResponse))
    , m_dataType(DataType::string)
    , m_stringData(std::move(data), std::move(type))
{
}

Response::Response(RawResponse rawResponse, float data, std::string unit)
    : m_rawResponse(std::move(rawResponse))
    , m_dataType(DataType::number)
    , m_floatData1(data, std::move(unit))
{
}

Response::Response(
    RawResponse rawResponse, float data1, std::string unit1, float data2, std::string unit2)
    : m_rawResponse(std::move(rawResponse))
    , m_dataType(DataType::numberPair)
    , m_floatData1(data1, std::move(unit1))
    , m_floatData2(data2, std::move(unit2))
{
}

std::ostream& operator<<(std::ostream& ost, const Response& resp)
{
    switch (resp.m_dataType) {
    case DataType::string:
        ost << "string: " << resp.m_stringData.first << ", " << resp.m_stringData.second << '\n';
        break;
    case DataType::number:
        ost << "float: " << resp.m_floatData1.first << ", " << resp.m_floatData1.second << '\n';
        break;
    case DataType::numberPair:
        ost << "float pair: " << resp.m_floatData1.first << ", " << resp.m_floatData1.second << '\n'
            << resp.m_floatData2.first << ", " << resp.m_floatData2.second << '\n';
        break;
    case DataType::dtc:
        ost << "dtc string: " << resp.m_stringData.first << ", " << resp.m_stringData.second
            << '\n';
        break;
    case DataType::bitset:
        ost << "bitset: " << resp.m_dataBitset << '\n';
        break;
    default:
        ost << "Empty response" << '\n';
        break;
    }
    return ost;
}
