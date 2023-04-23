#pragma once
#include "DecodeStrategy.hpp"

//Decodes:
//22 Fuel Rail Pressure (relative to manifold vacuum)
//-> 0-5177.265 kPa
class DecodeFuelRailPressure:public DecodeFloatStrategy
{
public :
    float decode(const std::string &text) const
    {
        if(text.length()!=5)
            throw std::runtime_error("invalid input");

        std::string byteA{text[0],text[1]};
        float valA=Utils::hexToDec(byteA);
        std::string byteB{text[3],text[4]};
        float valB=Utils::hexToDec(byteB);
        return 0.079*(256*valA+valB);
    }
};

//Decodes:
//23 Fuel Rail Gauge pressure (diesel, or gasoline direct injection)
//-> 0-655350 kPa
class DecodeFuelRailGaugePressure:public DecodeFloatStrategy
{
public :
    float decode(const std::string &text) const
    {
        if(text.length()!=5)
            throw std::runtime_error("invalid input");

        std::string byteA{text[0],text[1]};
        float valA=Utils::hexToDec(byteA);
        std::string byteB{text[3],text[4]};
        float valB=Utils::hexToDec(byteB);
        return 10*(256*valA+valB);
    }
};
