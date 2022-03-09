#pragma once
#include <iostream>
#include <gtest/gtest.h>
#include "../core/parameters-engine/ELM327/elm327-data-filters.h"

using namespace testing;

TEST(ELM327, DataFilters)
{
    Elm327DataFilters filter;
    std::string dataBytes;

    std::string CoolantTempResponse = "7E8 03 41 05 4B";
    std::string CoolantTempCommand = "0105";
    dataBytes = filter.FilterBytes(CoolantTempResponse, CoolantTempCommand, 2);
    EXPECT_EQ(dataBytes, "");
    dataBytes = filter.FilterBytes(CoolantTempResponse, CoolantTempCommand, 1);
    EXPECT_EQ(dataBytes, "4B");

    std::string EngineRpmResponse = "7E8 04 41 0C 0C 9C";
    std::string EngineRpmCommand = "010C";
    dataBytes = filter.FilterBytes(EngineRpmResponse, EngineRpmCommand, 1);
    EXPECT_EQ(dataBytes, "");
    dataBytes = filter.FilterBytes(EngineRpmResponse, EngineRpmCommand, 2);
    EXPECT_EQ(dataBytes, "0C9C");

    std::string PidsSupportedResponse = "7E8 06 41 00 98 3B 00 11";
    std::string PidsSupportedCommand = "0100";
    dataBytes = filter.FilterBytes(PidsSupportedResponse, PidsSupportedCommand, 3);
    EXPECT_EQ(dataBytes, "");
    dataBytes = filter.FilterBytes(PidsSupportedResponse, PidsSupportedCommand, 4);
    EXPECT_EQ(dataBytes, "983B0011");

}
