#include "response.hpp"

std::ostream& operator<<(std::ostream& ost, const Response& resp)
{
    switch (resp.dataType) {
    case DataType::string: {
        const auto& stringPair = std::get<StringData>(resp.decodedData);
        ost << "string: " << stringPair.first << ", " << stringPair.second << '\n';
        break;
    }
    case DataType::number: {
        const auto& floatData = std::get<FloatData>(resp.decodedData);
        ost << "float: " << floatData.first << floatData.second << '\n';
        break;
    }
    case DataType::numberPair: {
        const auto& floatDataPair = std::get<FloatDataPair>(resp.decodedData);
        ost << "float pair: "
            << floatDataPair.first.first << floatDataPair.first.second << ", "
            << floatDataPair.second.first << floatDataPair.second.second << '\n';
        break;
    }
    case DataType::dtc: {
        const auto& dtcString = std::get<StringData>(resp.decodedData);
        ost << "dtc string: " << dtcString.first << ", " << dtcString.second << '\n';
        break;
    }
    case DataType::bitset:
        ost << "bitset: " << std::get<Bitset_32>(resp.decodedData) << '\n';
        break;
    default:
        ost << "Empty response" << '\n';
        break;
    }
    return ost;
}
