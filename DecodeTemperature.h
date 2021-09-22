#pragma once
#include "DecodeFloatStrategy.h"
#include "utils.h"

//Returns -> -40-215°C
//Decodes:
//05 Engine Coolant temperature
//0F Air intake temperature
//46 Ambient air temperature
//5C Engine oil temperature
class DecodeTemperature: public DecodeFloatStrategy
{
public :
   std::optional<float> decode(std::string &text) const
   {
       if(text.length()!=2)
          return std::nullopt;

       std::string byteA{text[0],text[1]};
       return utils::hexToDec(byteA)-40;
   }
};

//Decodes:
//3C-3F Catalyst temperature
//-> -40-6513.5°C
class DecodeCatalystTemperature:public DecodeFloatStrategy
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
       return (256*valA+valB)/10-40;
   }
};
