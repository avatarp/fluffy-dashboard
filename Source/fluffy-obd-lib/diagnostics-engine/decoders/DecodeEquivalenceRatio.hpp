#pragma once
#include "DecodeStrategy.hpp"

//Decodes:
//24-2B,34-3B (AB) Air-Fuel Equivalence Ratio (lambda,λ)
//-> 0-2
class DecodeEquivalenceRatio:public DecodeFloatStrategy
{
public :
    float decode(const std::string &text) const
    {
        if(text.length()!=5)
            throw std::runtime_error("invalid input");

        std::string byteA{text[0],text[1]};
        std::string byteB{text[3],text[4]};
        float valA=Utils::hexToDec(byteA);
        float valB=Utils::hexToDec(byteB);
        return 2.0/65536.0*(256.0*valA+valB);
    }
};
