#include "response.hpp"

std::ostream& operator<<(std::ostream& ost, const Response& resp)
{
    switch (resp.m_dataType) {
    case DataType::string:
        ost << "string: " << resp.m_dataString.first << ", " << resp.m_dataString.second << '\n';
        break;
    case DataType::number:
        ost << "float: " << resp.m_dataFloat1.first << ", " << resp.m_dataFloat1.second << '\n';
        break;
    case DataType::numberPair:
        ost << "float pair: " << resp.m_dataFloat1.first << ", " << resp.m_dataFloat1.second << '\n'
            << resp.m_dataFloat2.first << ", " << resp.m_dataFloat2.second << '\n';
        break;
    case DataType::dtc:
        ost << "dtc string: " << resp.m_dataString.first << ", " << resp.m_dataString.second
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
