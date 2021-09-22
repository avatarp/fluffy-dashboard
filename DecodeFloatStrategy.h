#pragma once
#include <optional>

class DecodeFloatStrategy
{
public:
    virtual ~DecodeFloatStrategy(){}
    virtual std::optional<float> decode(std::string &text)const=0;
};
