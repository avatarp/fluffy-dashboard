#pragma once
#include "DecodeStrategy.h"
#include "../utils.h"

//Decodes:
//0D Speed -> 0-255km/h
//OB Intake manifold absolute pressure -> 0-255kPa
//1C OBD standard -> 0-255 enum
//30 Warm-ups since codes cleared -> 0-255 count
//33 Absolute Barometric Pressure -> 0-255 kPa
class DecodeSimpleA : public DecodeFloatStrategy
{
public :
   std::optional<float> decode(std::string &text) const
   {
       if(text.length()!=2)
          return std::nullopt;

       std::string byteA{text[0],text[1]};
       return utils::hexToDec(byteA);
   }
};
