#pragma once
#include "DecodeStrategy.h"

//Decodes:
//22 Run time -> 0-65535 seconds
//21 Distance with Malfunction Indicator Lamp on -> 0-65535 km
//31 Distance since coded cleared -> 0-65535km
class DecodeSimpleAB:public DecodeFloatStrategy
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
        return 256*valA+valB;
    }
};
