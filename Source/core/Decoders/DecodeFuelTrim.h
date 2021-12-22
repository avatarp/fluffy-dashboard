#pragma once
#include "DecodeStrategy.h"
#include "../utils.h"


//Decodes:
//06-09 Short/Long term fuel trim bank1/2
//Returns -> -100-99.2 % (-100 too rich - 99.2 too lean)
//14-1B Short term fuel trim Oxygen sensor 1-8
//Returns -> -100-99.2 % (-100 too rich - 99.2 too lean)
class DecodeFuelPressure:public DecodeFloatStrategy
{
public :
   std::optional<float> decode(std::string &text) const
   {
       if(text.length()!=2)
          return std::nullopt;

       std::string byteA{text[0],text[1]};
       float valA=utils::hexToDec(byteA);
       return 100/128*valA-100;
   }
};
