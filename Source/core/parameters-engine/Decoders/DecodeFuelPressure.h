#pragma once
#include "DecodeStrategy.h"

//Decodes
//0A Fuel pressure -> 0-765 kPa
class DecodeFuelPressure:public DecodeFloatStrategy
{
public :
    float decode(const std::string &text) const
    {
        if(text.length()!=2)
            throw std::runtime_error("invalid input");

        std::string byteA{text[0],text[1]};
        float valA=Utils::hexToDec(byteA);
        return 3*valA;
    }
};
