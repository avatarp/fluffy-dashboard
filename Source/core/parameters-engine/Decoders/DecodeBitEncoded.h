#pragma once
#include "DecodeStrategy.h"

//Decodes
//PIDs supported 00, 20, 40, 60, 80, A0, C0
//12 Commanded secondary air status
//13 Oxygen sensors present (in 2 banks)
//1D Oxygen sensors present (in 4 banks)
//1E Auxiliary input status
class DecodeBitEncoded:public DecodeBitEncodedStrategy
{
public :
    std::bitset<32> decode(const std::string &text) const
    {
        if(text.length()<2)
            throw std::runtime_error("invalid input");

        return std::bitset<32>(Utils::hexToBin(text));
    }
};
