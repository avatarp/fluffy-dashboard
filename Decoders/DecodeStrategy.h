#pragma once
#include <optional>
#include <bitset>

class DecodeFloatStrategy
{
public:
    virtual ~DecodeFloatStrategy(){}
    virtual std::optional<float> decode(std::string &text)const=0;
};

class DecodeBitEncodedStrategy
{
public:
    virtual ~DecodeBitEncodedStrategy(){}
    virtual std::optional<std::bitset<32>> decode(std::string &text)const=0;
};
