#pragma once
#include "DecodeStrategy.h"

//Decodes 14-1B Oxygen sensor voltage (A)
//-> -0-1.275 V
class DecodeOxygenSensorVoltage1: public DecodeFloatStrategy
{
public :
   float decode(const std::string &text) const
   {
       if(text.length()!=2)
          throw std::runtime_error("invalid input");

       std::string byteA{text[0],text[1]};
       return Utils::hexToDec(byteA)/200.0;
   }
};

//Decodes 24-2B Oxygen sensor voltage (CD)
//-> 0-7.999 V
class DecodeOxygenSensorVoltage2: public DecodeFloatStrategy
{
public :
   float decode(const std::string &text) const
   {
       if(text.length()!=5)
          throw std::runtime_error("invalid input");

       std::string byteC{text[0],text[1]};
       std::string byteD{text[3],text[4]};
       float valC = Utils::hexToDec(byteC);
       float valD = Utils::hexToDec(byteD);
       return 8.0/65536.0*(256.0*valC+valD);
   }
};
