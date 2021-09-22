#pragma once
#include <gtest/gtest.h>
#include <optional>
#include "../obd.h"
#include "../DecodeFloatStrategy.h"
#include "../DecodeRPM.h"
#include "../DecodeSimpleA.h"
#include "../DecodeTemperature.h"
#include "../DecodePercentage.h"
#include "../DecodeAirFlow.h"
#include "../DecodeTimingAdvance.h"
#include "../DecodeFuelPressure.h"
#include "../DecodeSimpleAB.h"
#include "../DecodeFuelRailPressure.h"
#include "../DecodeOxygenSensorVoltage.h"
#include "../DecodeOxygenSensorCurrent.h"
#include "../DecodeEquivalenceRatio.h"

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
