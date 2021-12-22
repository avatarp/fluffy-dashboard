#pragma once

#include "DecodeStrategy.h"
#include "../utils.h"

//Decodes
//PIDs supported 00, 20, 40, 60, 80, A0, C0
//12 Commanded secondary air status
//13 Oxygen sensors present (in 2 banks)
//1D Oxygen sensors present (in 4 banks)
//1E Auxiliary input status
class DecodeBitEncoded:public DecodeBitEncodedStrategy
{
public :
   std::optional<std::bitset<32>> decode(std::string &text) const
   {
       if(text.length()<8)
          return std::nullopt;

       return std::bitset<32>(utils::hexToBin(text));
   }
};
