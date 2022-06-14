#pragma once
#include <string>
#include <bitset>

enum class DataType
{
    string,
    bitset,
    number,
    pair,
    dtc
};

struct Response
{
DataType dataType;
std::string dataStr;
std::bitset<32> dataBitset;
float dataFloat;
std::string unit1;
std::string unit2;
};

