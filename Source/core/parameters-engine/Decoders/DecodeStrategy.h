#pragma once
#include <optional>
#include <bitset>
#include <sstream>

class DecodeFloatStrategy
{
public:
    virtual ~DecodeFloatStrategy(){}
    virtual std::optional<float> decode(const std::string &text)const=0;
};

class DecodeBitEncodedStrategy
{
public:
    virtual ~DecodeBitEncodedStrategy(){}
    virtual std::optional<std::bitset<32>> decode(const std::string &text)const=0;
};

class DecodeString{
public:
    virtual std::optional<std::string> decode(const std::string &text)
    {
        std::string result;
        result.reserve(text.size()/2);
        for(size_t i=0; i< text.length() ; i+=2)
        {
            std::string byte = text.substr(i,2);
            char chr = (char) (int)strtol(byte.c_str(), nullptr, 16);
            result.push_back(chr);
        }

        if(result.size()==0)
            return std::nullopt;

        return result;
    }
};

namespace Utils {

inline long hexToDec(std::string &hex)
{
    return strtol( hex.c_str(), nullptr, 16 );
}

inline std::string hexToBin(std::string hex)
{
    std::string result;
    for (unsigned i = 0; i < hex.length(); ++i)
    {
        switch (tolower(hex[i]))
        {
        case '0': result.append ("0000"); break;
        case '1': result.append ("0001"); break;
        case '2': result.append ("0010"); break;
        case '3': result.append ("0011"); break;
        case '4': result.append ("0100"); break;
        case '5': result.append ("0101"); break;
        case '6': result.append ("0110"); break;
        case '7': result.append ("0111"); break;
        case '8': result.append ("1000"); break;
        case '9': result.append ("1001"); break;
        case 'a': result.append ("1010"); break;
        case 'b': result.append ("1011"); break;
        case 'c': result.append ("1100"); break;
        case 'd': result.append ("1101"); break;
        case 'e': result.append ("1110"); break;
        case 'f': result.append ("1111"); break;
        default: break;
        }
    }
    return result;
}


inline int twoComplementaryHexToDec(std::string hexString)
{
    unsigned long long tempValue;
    std::istringstream ost(hexString);
    ost >> std::hex >> tempValue;
    std::bitset<8> binary(tempValue);

    if(binary.test(7))
    {
        binary.reset(7);
        int temp = (int)binary.to_ulong();
        temp -= 128;
        return temp;
    }
    return (int)binary.to_ulong();
}
}
