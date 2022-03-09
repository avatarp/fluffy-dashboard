#pragma once
#include "DecodeStrategy.h"


//Decodes 10 Mass Air Flow
//-> 0-655.35 gram/second
class DecodeAirFlow:public DecodeFloatStrategy
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
       return (256*valA+valB)/100;
   }
};
