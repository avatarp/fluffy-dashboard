#pragma once
#include "DecodeStrategy.h"

//Returns -> 0-100%
//Decodes:
//04 Engine load
//11 Throttle position
//2C Commanded EGR
//2E Commanded evaporative purge
//2F Fuel tank level input
class DecodePercentage: public DecodeFloatStrategy
{
public :
    float decode(const std::string &text) const
    {
        if(text.length()!=2)
            throw std::runtime_error("invalid input");

        std::string byteA{text[0],text[1]};
        return Utils::hexToDec(byteA)/2.55;
    }
};

//Returns -> -100-99.2%
//Decodes:
//06-09 Short/long fuel trim (-100 too rich - 99.2 too lean)
//14-1B Oxygen sensor short fuel trim (B)
//2D EGR error
class DecodeSignedPercentage: public DecodeFloatStrategy
{
public :
    float decode(const std::string &text) const
    {
        if(text.length()!=2)
            throw std::runtime_error("invalid input");

        std::string byteA{text[0],text[1]};
        return Utils::hexToDec(byteA)/1.28-100;
    }
};


