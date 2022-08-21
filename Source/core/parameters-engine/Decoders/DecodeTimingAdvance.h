#pragma once
#include "DecodeStrategy.h"

//Decodes 0E Timing advance
//-> -64-63.5° (before Top Dead Centre)
class DecodeTimingAdvance: public DecodeFloatStrategy
{
public :
    float decode(const std::string &text) const
    {
        if(text.length()!=2)
            throw std::runtime_error("invalid input");

        std::string byteA{text[0],text[1]};
        return Utils::hexToDec(byteA)/2.0-64;
    }
};
