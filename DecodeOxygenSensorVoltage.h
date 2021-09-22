#pragma once
#include "DecodeFloatStrategy.h"
#include "utils.h"

//Decodes 14-1B Oxygen sensor voltage (A)
//-> -0-1.275 V
class DecodeOxygenSensorVoltage1: public DecodeFloatStrategy
{
public :
   std::optional<float> decode(std::string &text) const
   {
       if(text.length()!=2)
          return std::nullopt;

       std::string byteA{text[0],text[1]};
       return utils::hexToDec(byteA)/200.0;
   }
};

//Decodes 24-2B Oxygen sensor voltage (CD)
//-> 0-7.999 V
class DecodeOxygenSensorVoltage2: public DecodeFloatStrategy
{
public :
   std::optional<float> decode(std::string &text) const
   {
       if(text.length()!=5)
          return std::nullopt;

       std::string byteC{text[0],text[1]};
       std::string byteD{text[3],text[4]};
       float valC = utils::hexToDec(byteC);
       float valD = utils::hexToDec(byteD);
       return 8.0/65536.0*(256.0*valC+valD);
   }
};
