#pragma once
#include "DecodeFloatStrategy.h"
#include "utils.h"


//Decodes:
//22 Fuel Rail Pressure (relative to manifold vacuum)
//-> 0-5177.265 kPa
class DecodeFuelRailPressure:public DecodeFloatStrategy
{
public :
   std::optional<float> decode(std::string &text) const
   {
       if(text.length()!=5)
          return std::nullopt;

       std::string byteA{text[0],text[1]};
       float valA=utils::hexToDec(byteA);
       std::string byteB{text[3],text[4]};
       float valB=utils::hexToDec(byteB);
       return 0.079*(256*valA+valB);
   }
};

//Decodes:
//23 Fuel Rail Gauge pressure (diesel, or gasoline direct injection)
//-> 0-655350 kPa
class DecodeFuelRailGaugePressure:public DecodeFloatStrategy
{
public :
   std::optional<float> decode(std::string &text) const
   {
       if(text.length()!=5)
          return std::nullopt;

       std::string byteA{text[0],text[1]};
       float valA=utils::hexToDec(byteA);
       std::string byteB{text[3],text[4]};
       float valB=utils::hexToDec(byteB);
       return 10*(256*valA+valB);
   }
};
