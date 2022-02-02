#pragma once
#include "DecodeStrategy.h"
#include "../utils.h"

//Decodes
//32 Evap. system Vapor pressure
//-> -8192-8191.75 Pa
//TODO: A & B are two's complement signed
class DecodeEvapPressure:public DecodeFloatStrategy
{
public :
   std::optional<float> decode(std::string &text) const
   {
       if(text.length()!=5)
          return std::nullopt;

       std::string byteA{text[0],text[1]};
       float valA=utils::twoComplementaryHexToDec(byteA);
       std::string byteB{text[3],text[4]};
       float valB=utils::twoComplementaryHexToDec(byteB);
       return 0.25*(256*valA+valB);
   }
};
