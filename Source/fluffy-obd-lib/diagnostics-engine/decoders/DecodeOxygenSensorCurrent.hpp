#pragma once
#include "DecodeStrategy.hpp"

//Decodes 34-3B Oxygen sensor current (CD)
//-> -128-127.996 mA
class DecodeOxygenSensorCurrent: public DecodeFloatStrategy
{
public :
    float decode(const std::string &text) const
    {
        if(text.length()!=5)
            throw std::runtime_error("invalid input");

        std::string byteC{text[0],text[1]};
        float valC=Utils::hexToDec(byteC);
        std::string byteD{text[3],text[4]};
        float valD=Utils::hexToDec(byteD);
        return (256.0*valC+valD)/256.0-128.0;
    }
};
