#pragma once
#include <string>

class UnitType
{
public:
   const std::string symbol;
   const std::string name;
    UnitType();
    virtual ~UnitType()=0;
    std::string getSymbol(){
        return symbol;
    }
    std::string getName(){
        return name;
    }
};
