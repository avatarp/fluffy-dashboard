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
    DecodeFloatStrategy *strat=new DecodeRPM();

    std::string zero="00 00";
    std::optional<float> resultZero = strat->decode(zero);
    ASSERT_TRUE(resultZero);
    EXPECT_EQ(*resultZero,0.0);

    std::string RPM807="0C 9C";
    std::optional<float> result807 = strat->decode(RPM807);
    ASSERT_TRUE(result807);
    EXPECT_EQ(*result807,807);

    std::string rpmMax="FF FF";
    std::optional<float> resultMax = strat->decode(rpmMax);
    ASSERT_TRUE(resultMax);
    EXPECT_EQ(*resultMax,16383.75);
}

TEST(decodeSpeed, decoders)
{
    DecodeFloatStrategy *strat = new DecodeSimpleA();

    std::string zero="00";
    std::optional<float> resultZero = strat->decode(zero);
    ASSERT_TRUE(resultZero);
    EXPECT_EQ(*resultZero,0.0);

    std::string speed17="11";
    std::optional<float> result17 = strat->decode(speed17);
    ASSERT_TRUE(result17);
    EXPECT_EQ(*result17,17);

    std::string speedMax="FF";
    std::optional<float> resultMax = strat->decode(speedMax);
    ASSERT_TRUE(resultMax);
    EXPECT_EQ(*resultMax,255);
}

TEST(decodeTemperature, decoders)
{
    DecodeFloatStrategy *strat = new DecodeTemperature();

    std::string zero="00";
    std::optional<float> resultZero = strat->decode(zero);
    ASSERT_TRUE(resultZero);
    EXPECT_EQ(*resultZero,-40);

    std::string temp1="29";
    std::optional<float> result1 = strat->decode(temp1);
    ASSERT_TRUE(result1);
    EXPECT_EQ(*result1,1);

    std::string tempMax="FF";
    std::optional<float> resultMax = strat->decode(tempMax);
    ASSERT_TRUE(resultMax);
    EXPECT_EQ(*resultMax,215);
}

TEST(decodePercentage, decoders)
{
    DecodeFloatStrategy *strat = new DecodePercentage();

    std::string zero="00";
    std::optional<float> resultZero = strat->decode(zero);
    ASSERT_TRUE(resultZero);
    EXPECT_EQ(*resultZero,0);

    std::string percentage16="29";
    std::optional<float> result16 = strat->decode(percentage16);
    ASSERT_TRUE(result16);
    EXPECT_NEAR(*result16,16.0784,0.0001);

    std::string percentageMax="FF";
    std::optional<float> resultMax = strat->decode(percentageMax);
    ASSERT_TRUE(resultMax);
    EXPECT_EQ(*resultMax,100);
}

TEST(decodeAirFlow, decoders)
{
    DecodeFloatStrategy *strat = new DecodeAirFlow();

    std::string zero="00 00";
    std::optional<float> resultZero = strat->decode(zero);
    ASSERT_TRUE(resultZero);
    EXPECT_EQ(*resultZero,0);

    std::string airFlow40="10 01";
    std::optional<float> result40 = strat->decode(airFlow40);
    ASSERT_TRUE(result40);
    EXPECT_NEAR(*result40,40.97,0.0001);

    std::string percentageMax="FF FF";
    std::optional<float> resultMax = strat->decode(percentageMax);
    ASSERT_TRUE(resultMax);
    EXPECT_NEAR(*resultMax,655.35,0.0001);
}

TEST(decodeTimingAdvance, decoders)
{
    DecodeFloatStrategy *strat = new DecodeTimingAdvance();

    std::string min="00";
    std::optional<float> resultMin = strat->decode(min);
    ASSERT_TRUE(resultMin);
    EXPECT_EQ(*resultMin,-64);

    std::string val="10";
    std::optional<float> result = strat->decode(val);
    ASSERT_TRUE(result);
    EXPECT_NEAR(*result,-56,0.0001);

    std::string percentageMax="FF";
    std::optional<float> resultMax = strat->decode(percentageMax);
    ASSERT_TRUE(resultMax);
    EXPECT_NEAR(*resultMax,63.5,0.0001);
}

TEST(decodeFuelPressure, decoders)
{
    DecodeFloatStrategy *strat = new DecodeFuelPressure();

    std::string min="00";
    std::optional<float> resultMin = strat->decode(min);
    ASSERT_TRUE(resultMin);
    EXPECT_EQ(*resultMin,0);

    std::string val="10";
    std::optional<float> result = strat->decode(val);
    ASSERT_TRUE(result);
    EXPECT_NEAR(*result,48,0.0001);

    std::string percentageMax="FF";
    std::optional<float> resultMax = strat->decode(percentageMax);
    ASSERT_TRUE(resultMax);
    EXPECT_NEAR(*resultMax,765,0.0001);
}

TEST(DecodeSimpleAB, decoders)
{
    DecodeFloatStrategy *strat = new DecodeSimpleAB();

    std::string min="00 00";
    std::optional<float> resultMin = strat->decode(min);
    ASSERT_TRUE(resultMin);
    EXPECT_EQ(*resultMin,0);

    std::string val="10 00";
    std::optional<float> result = strat->decode(val);
    ASSERT_TRUE(result);
    EXPECT_NEAR(*result,4096,0.0001);

    std::string valMax="FF FF";
    std::optional<float> resultMax = strat->decode(valMax);
    ASSERT_TRUE(resultMax);
    EXPECT_NEAR(*resultMax,65535,0.0001);
}

TEST(decodeFuelRailPressure, decoders)
{
    DecodeFloatStrategy *strat = new DecodeFuelRailPressure();

    std::string min="00 00";
    std::optional<float> resultMin = strat->decode(min);
    ASSERT_TRUE(resultMin);
    EXPECT_EQ(*resultMin,0);

    std::string val="10 00";
    std::optional<float> result = strat->decode(val);
    ASSERT_TRUE(result);
    EXPECT_NEAR(*result,323.584,0.001);

    std::string valMax="FF FF";
    std::optional<float> resultMax = strat->decode(valMax);
    ASSERT_TRUE(resultMax);
    EXPECT_NEAR(*resultMax,5177.265,0.001);
}

TEST(decodeRunTime, decoders)
{
    DecodeFloatStrategy *strat = new DecodeFuelRailGaugePressure();

    std::string min="00 00";
    std::optional<float> resultMin = strat->decode(min);
    ASSERT_TRUE(resultMin);
    EXPECT_EQ(*resultMin,0);

    std::string val="10 00";
    std::optional<float> result = strat->decode(val);
    ASSERT_TRUE(result);
    EXPECT_NEAR(*result,40960,0.0001);

    std::string valMax="FF FF";
    std::optional<float> resultMax = strat->decode(valMax);
    ASSERT_TRUE(resultMax);
    EXPECT_NEAR(*resultMax,655350,0.0001);
}

TEST(decodeSignedPercentage, decoders)
{
    DecodeFloatStrategy *strat = new DecodeSignedPercentage();

    std::string min="00";
    std::optional<float> resultMin = strat->decode(min);
    ASSERT_TRUE(resultMin);
    EXPECT_EQ(*resultMin,-100);

    std::string val="10";
    std::optional<float> result = strat->decode(val);
    ASSERT_TRUE(result);
    EXPECT_NEAR(*result,-87.5,0.01);

    std::string valMax="FF";
    std::optional<float> resultMax = strat->decode(valMax);
    ASSERT_TRUE(resultMax);
    EXPECT_NEAR(*resultMax,99.21,0.01);
}

TEST(decodeCatalystTemperature, decoders)
{
    DecodeFloatStrategy *strat = new DecodeCatalystTemperature();

    std::string min="00 00";
    std::optional<float> resultMin = strat->decode(min);
    ASSERT_TRUE(resultMin);
    EXPECT_EQ(*resultMin,-40);

    std::string val="10 00";
    std::optional<float> result = strat->decode(val);
    ASSERT_TRUE(result);
    EXPECT_NEAR(*result,369.6,0.0001);

    std::string valMax="FF FF";
    std::optional<float> resultMax = strat->decode(valMax);
    ASSERT_TRUE(resultMax);
    EXPECT_NEAR(*resultMax,6513.5,0.0001);
}

TEST(decodeOxygenSensorVoltage1, decoders)
{
    DecodeFloatStrategy *strat = new DecodeOxygenSensorVoltage1();

    std::string min="00";
    std::optional<float> resultMin = strat->decode(min);
    ASSERT_TRUE(resultMin);
    EXPECT_EQ(*resultMin,0);

    std::string val="10";
    std::optional<float> result = strat->decode(val);
    ASSERT_TRUE(result);
    EXPECT_NEAR(*result,0.08,0.0001);

    std::string valMax="FF";
    std::optional<float> resultMax = strat->decode(valMax);
    ASSERT_TRUE(resultMax);
    EXPECT_NEAR(*resultMax,1.275,0.0001);
}

TEST(decodeOxygenSensorVoltage2, decoders)
{
    DecodeFloatStrategy *strat = new DecodeOxygenSensorVoltage2();

    std::string min="00 00";
    std::optional<float> resultMin = strat->decode(min);
    ASSERT_TRUE(resultMin);
    EXPECT_EQ(*resultMin,0);

    std::string val="10 00";
    std::optional<float> result = strat->decode(val);
    ASSERT_TRUE(result);
    EXPECT_NEAR(*result,0.5,0.0001);

    std::string valMax="FF FF";
    std::optional<float> resultMax = strat->decode(valMax);
    ASSERT_TRUE(resultMax);
    EXPECT_NEAR(*resultMax,7.9999,0.0001);
}

TEST(decodeEquivalenceRatio, decoders)
{
    DecodeFloatStrategy *strat = new DecodeEquivalenceRatio();

    std::string min="00 00";
    std::optional<float> resultMin = strat->decode(min);
    ASSERT_TRUE(resultMin);
    EXPECT_EQ(*resultMin,0);

    std::string val="10 00";
    std::optional<float> result = strat->decode(val);
    ASSERT_TRUE(result);
    EXPECT_NEAR(*result,0.125,0.0001);

    std::string valMax="FF FF";
    std::optional<float> resultMax = strat->decode(valMax);
    ASSERT_TRUE(resultMax);
    EXPECT_NEAR(*resultMax,2.0,0.0001);
}

TEST(decodeOxygenSensorCurrent, decoders)
{
    DecodeFloatStrategy *strat = new DecodeOxygenSensorCurrent();

    std::string min="00 00";
    std::optional<float> resultMin = strat->decode(min);
    ASSERT_TRUE(resultMin);
    EXPECT_NEAR(*resultMin,-128,0.0001);

    std::string val="10 00";
    std::optional<float> result = strat->decode(val);
    ASSERT_TRUE(result);
    EXPECT_NEAR(*result,-112,0.0001);

    std::string valMax="FF FF";
    std::optional<float> resultMax = strat->decode(valMax);
    ASSERT_TRUE(resultMax);
    EXPECT_NEAR(*resultMax,127.996,0.0001);
}

TEST(decodeEvapPressure, decoders)
{

    DecodeFloatStrategy *strat = new DecodeEvapPressure();

    std::string zero="00 00";
    std::optional<float> resultZero = strat->decode(zero);
    ASSERT_TRUE(resultZero);
    ASSERT_NEAR(*resultZero, 0, 0.0001);

    std::string min = "80 00";
    std::optional<float> resultMin = strat->decode(min);
    ASSERT_TRUE(resultMin);
    ASSERT_NEAR(*resultMin, -8192.0, 0.0001);

    std::string valMax = "7F FF";
    std::optional<float> resultMax = strat->decode(valMax);
    ASSERT_TRUE(resultMax);
    ASSERT_NEAR(*resultMax, 8191.75, 0.0001);
}

TEST(decodeBitEncoded, decoders)
{
    DecodeBitEncodedStrategy *strat = new DecodeBitEncoded();

    std::string min = "00000000";
    std::optional<std::bitset<32>> resultMin = strat->decode(min);
    ASSERT_TRUE(resultMin);
    EXPECT_EQ(*resultMin, std::bitset<32>(0b00000000000000000000000000000000));

    std::string val = "BE1FA813";
    std::optional<std::bitset<32>> result = strat->decode(val);
    ASSERT_TRUE(result);
    EXPECT_EQ(*result, std::bitset<32>(0b10111110000111111010100000010011));

    std::string valMax = "FFFFFFFF";
    std::optional<std::bitset<32>> resultMax = strat->decode(valMax);
    ASSERT_TRUE(resultMax);
    EXPECT_EQ(*resultMax, std::bitset<32>(0b11111111111111111111111111111111));

}

TEST(decodeString, decoders)
{
    DecodeString decoder;

    std::optional<std::string> result = decoder.decode("");
    ASSERT_FALSE(result);

    std::string vin = "57463055585847414A5532473830353439";
    result = decoder.decode(vin);
    ASSERT_TRUE(result);
    EXPECT_EQ(*result, "WF0UXXGAJU2G80549");
}


TEST(decodeDTC, decoders)
{
    DecodeDTC decoder;
    std::string dtc = "";
    std::optional<std::string> result = decoder.decode(dtc);
    ASSERT_FALSE(result);

    dtc = "4300";
    result = decoder.decode(dtc);
    ASSERT_TRUE(result);
    EXPECT_EQ(*result, "P0300");

    dtc = "4700";
    result = decoder.decode(dtc);
    ASSERT_TRUE(result);
    std::cout<<"dtc: "+*result<<std::endl;
    EXPECT_EQ(*result, "P0700");



}
