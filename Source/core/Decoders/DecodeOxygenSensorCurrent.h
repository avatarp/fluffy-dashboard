#pragma once
#include "DecodeStrategy.h"
#include "../utils.h"

//Decodes 34-3B Oxygen sensor current (CD)
//-> -128-127.996 mA
class DecodeOxygenSensorCurrent: public DecodeFloatStrategy
{
public :
   std::optional<float> decode(std::string &text) const
   {
       if(text.length()!=5)
          return std::nullopt;

       std::string byteC{text[0],text[1]};
       float valC=utils::hexToDec(byteC);
       std::string byteD{text[3],text[4]};
       float valD=utils::hexToDec(byteD);
       return (256.0*valC+valD)/256.0-128.0;
   }
};
