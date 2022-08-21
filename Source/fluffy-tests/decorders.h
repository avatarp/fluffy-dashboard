#pragma once
#include <gtest/gtest.h>
#include <optional>
#include <bitset>
#include "../core/parameters-engine/Decoders/DecodeStrategy.h"
#include "../core/parameters-engine/Decoders/DecodeRPM.h"
#include "../core/parameters-engine/Decoders/DecodeSimpleA.h"
#include "../core/parameters-engine/Decoders/DecodeTemperature.h"
#include "../core/parameters-engine/Decoders/DecodePercentage.h"
#include "../core/parameters-engine/Decoders/DecodeAirFlow.h"
#include "../core/parameters-engine/Decoders/DecodeTimingAdvance.h"
#include "../core/parameters-engine/Decoders/DecodeFuelPressure.h"
#include "../core/parameters-engine/Decoders/DecodeSimpleAB.h"
#include "../core/parameters-engine/Decoders/DecodeFuelRailPressure.h"
#include "../core/parameters-engine/Decoders/DecodeOxygenSensorVoltage.h"
#include "../core/parameters-engine/Decoders/DecodeOxygenSensorCurrent.h"
#include "../core/parameters-engine/Decoders/DecodeEquivalenceRatio.h"
#include "../core/parameters-engine/Decoders/DecodeBitEncoded.h"
#include "../core/parameters-engine/Decoders/DecodeEvapPressure.h"
#include "../core/parameters-engine/Decoders/DecodeDTC.h"

using namespace testing;

TEST(decodeRPM, decoders)
{
    DecodeRPM decoder;

    std::string zero="00 00";
    EXPECT_EQ(decoder.decode(zero),0.0);

    std::string RPM807="0C 9C";
    EXPECT_EQ(decoder.decode(RPM807),807);

    std::string rpmMax="FF FF";
    EXPECT_NEAR(decoder.decode(rpmMax),16383.75,0.001);
}

TEST(decodeSpeed, decoders)
{
    DecodeSimpleA decoder;

    std::string zero="00";
    EXPECT_EQ(decoder.decode(zero),0.0);

    std::string speed17="11";
    EXPECT_EQ(decoder.decode(speed17),17);

    std::string speedMax="FF";
    EXPECT_EQ(decoder.decode(speedMax),255);
}

TEST(decodeTemperature, decoders)
{
    DecodeTemperature decoder;

    std::string zero="00";
    EXPECT_EQ(decoder.decode(zero),-40);

    std::string temp1="29";
    EXPECT_EQ(decoder.decode(temp1),1);

    std::string tempMax="FF";
    EXPECT_EQ(decoder.decode(tempMax),215);
}

TEST(decodePercentage, decoders)
{
    DecodePercentage decoder;

    std::string zero="00";
    EXPECT_EQ(decoder.decode(zero),0);

    std::string percentage16="29";
    EXPECT_NEAR(decoder.decode(percentage16),16.0784,0.0001);

    std::string percentageMax="FF";
    EXPECT_EQ(decoder.decode(percentageMax),100);
}

TEST(decodeAirFlow, decoders)
{
    DecodeAirFlow decoder;

    std::string zero="00 00";
    EXPECT_EQ(decoder.decode(zero),0);

    std::string airFlow40="10 01";
    EXPECT_NEAR(decoder.decode(airFlow40),40.97,0.0001);

    std::string percentageMax="FF FF";
    EXPECT_NEAR(decoder.decode(percentageMax),655.35,0.0001);
}

TEST(decodeTimingAdvance, decoders)
{
    DecodeTimingAdvance decoder;

    std::string min="00";
    EXPECT_EQ(decoder.decode(min),-64);

    std::string val="10";
    EXPECT_NEAR(decoder.decode(val),-56,0.0001);

    std::string percentageMax="FF";
    EXPECT_NEAR(decoder.decode(percentageMax),63.5,0.0001);
}

TEST(decodeFuelPressure, decoders)
{
    DecodeFuelPressure decoder;

    std::string min="00";
    EXPECT_EQ(decoder.decode(min),0);

    std::string val="10";
    EXPECT_NEAR(decoder.decode(val),48,0.0001);

    std::string percentageMax="FF";
    EXPECT_NEAR(decoder.decode(percentageMax),765,0.0001);
}

TEST(DecodeSimpleAB, decoders)
{
    DecodeSimpleAB decoder;

    std::string min="00 00";
    EXPECT_EQ(decoder.decode(min),0);

    std::string val="10 00";
    EXPECT_NEAR(decoder.decode(val),4096,0.0001);

    std::string valMax="FF FF";
    EXPECT_NEAR(decoder.decode(valMax),65535,0.0001);
}

TEST(decodeFuelRailPressure, decoders)
{
    DecodeFuelRailPressure decoder;

    std::string min="00 00";
    EXPECT_EQ(decoder.decode(min),0);

    std::string val="10 00";
    EXPECT_NEAR(decoder.decode(val),323.584,0.001);

    std::string valMax="FF FF";
    EXPECT_NEAR(decoder.decode(valMax),5177.265,0.001);
}

TEST(decodeRunTime, decoders)
{
    DecodeFuelRailGaugePressure decoder;

    std::string min="00 00";
    EXPECT_EQ(decoder.decode(min),0);

    std::string val="10 00";
    EXPECT_NEAR(decoder.decode(val),40960,0.0001);

    std::string valMax="FF FF";
    EXPECT_NEAR(decoder.decode(valMax),655350,0.0001);
}

TEST(decodeSignedPercentage, decoders)
{
    DecodeSignedPercentage decoder;

    std::string min="00";
    EXPECT_EQ(decoder.decode(min),-100);

    std::string val="10";
    EXPECT_NEAR(decoder.decode(val),-87.5,0.01);

    std::string valMax="FF";
    EXPECT_NEAR(decoder.decode(valMax),99.21,0.01);
}

TEST(decodeCatalystTemperature, decoders)
{
    DecodeCatalystTemperature decoder;

    std::string min="00 00";
    EXPECT_EQ(decoder.decode(min),-40);

    std::string val="10 00";
    EXPECT_NEAR(decoder.decode(val),369.6,0.0001);

    std::string valMax="FF FF";
    EXPECT_NEAR(decoder.decode(valMax),6513.5,0.0001);
}

TEST(decodeOxygenSensorVoltage1, decoders)
{
    DecodeOxygenSensorVoltage1 decoder;

    std::string min="00";
    EXPECT_EQ(decoder.decode(min),0);

    std::string val="10";
    EXPECT_NEAR(decoder.decode(val),0.08,0.0001);

    std::string valMax="FF";
    EXPECT_NEAR(decoder.decode(valMax),1.275,0.0001);
}

TEST(decodeOxygenSensorVoltage2, decoders)
{
    DecodeOxygenSensorVoltage2 decoder;

    std::string min="00 00";
    EXPECT_EQ(decoder.decode(min),0);

    std::string val="10 00";
    EXPECT_NEAR(decoder.decode(val),0.5,0.0001);

    std::string valMax="FF FF";
    EXPECT_NEAR(decoder.decode(valMax),7.9999,0.0001);
}

TEST(decodeEquivalenceRatio, decoders)
{
    DecodeEquivalenceRatio decoder;

    std::string min="00 00";
    EXPECT_EQ(decoder.decode(min),0);

    std::string val="10 00";
    EXPECT_NEAR(decoder.decode(val),0.125,0.0001);

    std::string valMax="FF FF";
    EXPECT_NEAR(decoder.decode(valMax),2.0,0.0001);
}

TEST(decodeOxygenSensorCurrent, decoders)
{
    DecodeOxygenSensorCurrent decoder;

    std::string min="00 00";
    EXPECT_NEAR(decoder.decode(min),-128,0.0001);

    std::string val="10 00";
    EXPECT_NEAR(decoder.decode(val),-112,0.0001);

    std::string valMax="FF FF";
    EXPECT_NEAR(decoder.decode(valMax),127.996,0.0001);
}

TEST(decodeEvapPressure, decoders)
{
    DecodeEvapPressure decoder;

    std::string zero="00 00";
    ASSERT_NEAR(decoder.decode(zero), 0, 0.0001);

    std::string min = "80 00";
    ASSERT_NEAR(decoder.decode(min), -8192.0, 0.0001);

    std::string valMax = "7F FF";
    ASSERT_NEAR(decoder.decode(valMax), 8191.75, 0.0001);
}

TEST(decodeBitEncoded, decoders)
{
    DecodeBitEncoded decoder;

    std::string min = "00000000";
    EXPECT_EQ(decoder.decode(min),
              std::bitset<32>(0b00000000000000000000000000000000));

    std::string val = "BE1FA813";
    EXPECT_EQ(decoder.decode(val),
              std::bitset<32>(0b10111110000111111010100000010011));

    std::string valMax = "FFFFFFFF";
    EXPECT_EQ(decoder.decode(valMax),
              std::bitset<32>(0b11111111111111111111111111111111));
}

TEST(decodeString, decoders)
{
    DecodeString decoder;

    EXPECT_EQ(decoder.decode(std::string()),"");

    std::string vin = "57463055585847414A5532473830353439";
    EXPECT_EQ(decoder.decode(vin), "WF0UXXGAJU2G80549");
}


TEST(decodeDTC, decoders)
{
    DecodeDTC decoder;

    EXPECT_THROW({
        decoder.decode(std::string());
    },std::runtime_error);

    std::string dtc = "4300";
    EXPECT_EQ(decoder.decode(dtc), "P0300");

    dtc = "4700";
    EXPECT_EQ(decoder.decode(dtc), "P0700");
}
