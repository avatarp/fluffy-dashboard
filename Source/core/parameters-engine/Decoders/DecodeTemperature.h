#pragma once
#include "DecodeStrategy.h"

//Returns -> -40-215°C
//Decodes:
//05 Engine Coolant temperature
//0F Air intake temperature
//46 Ambient air temperature
//5C Engine oil temperature
class DecodeTemperature: public DecodeFloatStrategy
{
public :
   float decode(const std::string &text) const
   {
       if(text.length()!=2)
          throw std::runtime_error("invalid input");

       std::string byteA{text[0],text[1]};
       return Utils::hexToDec(byteA)-40;
   }
};

//Decodes:
//3C-3F Catalyst temperature
//-> -40-6513.5°C
class DecodeCatalystTemperature:public DecodeFloatStrategy
{
public :
   float decode(const std::string &text) const
   {
       if(text.length()!=5)
          throw std::runtime_error("invalid input");

       std::string byteA{text[0],text[1]};
       float valA=Utils::hexToDec(byteA);
       std::string byteB{text[3],text[4]};
       float valB=Utils::hexToDec(byteB);
       return (256*valA+valB)/10-40;
   }
};
