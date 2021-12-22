#pragma once
#include "unittype.h"

class KilometersPerHour : public UnitType
{
    KilometersPerHour(){
        this->name = "Kilometers per hour";
        this->symbol = "km/h";
    }
};

class MetersPerSecond : public UnitType
{
    MetersPerSecond(){
        this->name = "Meters per second";
        this->symbol = "m/s";
    }
};

class MilesPerHour: public UnitType{
    MilesPerHour(){
    this->name = "Miles per hour";
    this->symbol = "mph"
    }
};
