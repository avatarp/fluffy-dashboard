#pragma once
#include "DecodeStrategy.h"

//Decodes
//0C Engine RPM -> 0-16 383.75 RPM
class DecodeRPM:public DecodeFloatStrategy
{
public :
   std::optional<float> decode(const std::string &text) const
   {
       if(text.length()!=5)
          return std::nullopt;

       std::string byteA{text[0],text[1]};
       std::string byteB{text[3],text[4]};
       float valA=Utils::hexToDec(byteA);
       float valB=Utils::hexToDec(byteB);
       return (256*valA+valB)/4;
   }
};
