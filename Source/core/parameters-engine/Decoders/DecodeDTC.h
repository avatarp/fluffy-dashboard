#pragma once
#include "DecodeStrategy.h"

class DecodeDTC
{
public:
    virtual std::optional<std::string> decode(const std::string &text)
    {
        if(text.length()<4)
            return std::nullopt;

        std::string dtc;

        char byte[1];
        text.copy(byte,1,text.size()-1);
        std::string byteA7 = Utils::hexToBin(byte);

        std::bitset<2> dtcLocation(byteA7.substr(0,2));
        switch (dtcLocation.to_ulong()) {
        case 0: dtc.push_back('P'); break;
        case 1: dtc.push_back('C'); break;
        case 2: dtc.push_back('B'); break;
        case 3: dtc.push_back('U'); break;
        default: break;
        }

        std::bitset<2> firstDigit(byteA7.substr(2,2));
        dtc.push_back(std::to_string(firstDigit.to_ulong())[0]);
        //insert rest of the dtc
        dtc.push_back(text.at(1));
        dtc.push_back(text.at(2));
        dtc.push_back(text.at(3));
        return dtc;
    }
};