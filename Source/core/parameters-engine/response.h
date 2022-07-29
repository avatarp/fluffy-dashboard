#pragma once
#include <string>
#include <bitset>
#include <utility>

enum class DataType
{
    empty,
    string,
    bitset,
    number,
    numberPair,
    dtc
};

struct Response
{
DataType dataType;
std::bitset<32> dataBitset;
std::pair<float, std::string> floatData1;
std::pair<float, std::string> floatData2;
std::pair<std::string, std::string> stringData;

Response();
Response(const std::bitset<32> &bitset);
Response(const std::string &data, const std::string &type);
Response(float data, const std::string &unit);
Response(float data1, const std::string &unit1, float data2, const std::string &unit2);
};

