#include "response.h"

Response::Response(){
    dataType = DataType::empty;
}

Response::Response(const std::bitset<32> &bitset)
{
    this->dataType = DataType::bitset;
    this->dataBitset = bitset;
}

Response::Response(const std::string &data, const std::string &type)
{
    this->dataType = DataType::string;
    stringData.first = data;
    stringData.second = type;
}

Response::Response(float data, const std::string &unit)
{
    this->dataType = DataType::number;
    floatData1.first = data;
    floatData1.second = unit;
}

Response::Response(float data1, const std::string &unit1,
                   float data2, const std::string &unit2)
{
    this->dataType = DataType::numberPair;
    this->floatData1.first = data1;
    this->floatData1.second = unit1;
    this->floatData2.first = data2;
    this->floatData2.second = unit2;
}
