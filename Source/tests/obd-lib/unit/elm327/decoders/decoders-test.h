#ifndef DECODERS_TEST_H_
#define DECODERS_TEST_H_

#include "elm327-decoders.hpp"
#include <bitset>

#include <gtest/gtest.h>

using namespace testing;
using namespace elm327::decoders;

TEST(elm327decoders, decodeBitEncoded)
{
    EXPECT_EQ(DecodeBitEncoded("00000000"),
        std::bitset<32>(0b00000000000000000000000000000000));

    EXPECT_EQ(DecodeBitEncoded("BE1FA813"),
        std::bitset<32>(0b10111110000111111010100000010011));

    EXPECT_EQ(DecodeBitEncoded("FFFFFFFF"),
        std::bitset<32>(0b11111111111111111111111111111111));
}

TEST(elm327decoders, decodeString)
{
    EXPECT_EQ(DecodeString(std::string()), "");

    std::string vin = "57463055585847414A5532473830353439";
    EXPECT_EQ("WF0UXXGAJU2G80549", DecodeString(vin));
}

TEST(elm327decoders, decodeCountA)
{
    EXPECT_EQ(0.0, DecodeCountA("00"));
    EXPECT_EQ(17, DecodeCountA("11"));
    EXPECT_EQ(255, DecodeCountA("FF"));
}

TEST(elm327decoders, DecodeCountAB)
{
    EXPECT_EQ(0, DecodeCountAB("0000"));
    EXPECT_NEAR(4096, DecodeCountAB("1000"), 0.0001);
    EXPECT_NEAR(65535, DecodeCountAB("FFFF"), 0.0001);
}

TEST(elm327decoders, decodeDTC)
{
    EXPECT_EQ("P3223", DecodeDTC("3223"));
    EXPECT_EQ("C0300", DecodeDTC("4300"));
    EXPECT_EQ("C0700", DecodeDTC("4700"));
    EXPECT_EQ("B3110", DecodeDTC("B110"));
    EXPECT_EQ("U0158", DecodeDTC("C158"));
}

TEST(elm327decoders, decodeAirFlow)
{
    EXPECT_EQ(0, DecodeAirFlow("00 0"));
    EXPECT_NEAR(40.97, DecodeAirFlow("1001"), 0.0001);
    EXPECT_NEAR(655.35, DecodeAirFlow("FFFF"), 0.0001);
}

TEST(elm327decoders, decodeEquivalenceRatio)
{
    EXPECT_EQ(0, DecodeEquivalenceRatio("0000"));
    EXPECT_NEAR(0.125, DecodeEquivalenceRatio("1000"), 0.0001);
    EXPECT_NEAR(2.0, DecodeEquivalenceRatio("FFFF"), 0.0001);
}

TEST(elm327decoders, decodeEvapPressure)
{
    ASSERT_NEAR(0, DecodeEvapPressure("0000"), 0.0001);
    ASSERT_NEAR(-8192.0, DecodeEvapPressure("8000"), 0.0001);
    ASSERT_NEAR(8191.75, DecodeEvapPressure("7FFF"), 0.0001);
}

TEST(elm327decoders, decodeFuelPressure)
{
    EXPECT_EQ(0, DecodeFuelPressure("00"));
    EXPECT_NEAR(48, DecodeFuelPressure("10"), 0.0001);
    EXPECT_NEAR(765, DecodeFuelPressure("FF"), 0.0001);
}

TEST(elm327decoders, decodeFuelRailPressure)
{
    EXPECT_EQ(0, DecodeFuelRailPressure("0000"));
    EXPECT_NEAR(323.584, DecodeFuelRailPressure("1000"), 0.001);
    EXPECT_NEAR(5177.265, DecodeFuelRailPressure("FFFF"), 0.001);
}

TEST(elm327decoders, decodeFuelRailGaugePressure)
{
    EXPECT_EQ(0, DecodeFuelRailGaugePressure("0000"));
    EXPECT_NEAR(40960, DecodeFuelRailGaugePressure("1000"), 0.0001);
    EXPECT_NEAR(655350, DecodeFuelRailGaugePressure("FFFF"), 0.0001);
}

TEST(elm327decoders, decodeOxygenSensorCurrent)
{
    EXPECT_NEAR(-128, DecodeOxygenSensorCurrent("0000"), 0.0001);
    EXPECT_NEAR(-112, DecodeOxygenSensorCurrent("1000"), 0.0001);
    EXPECT_NEAR(127.996, DecodeOxygenSensorCurrent("FFFF"), 0.0001);
}

TEST(elm327decoders, decodeOxygenSensorVoltage1)
{
    EXPECT_EQ(0, DecodeOxygenSensorVoltage1("00"));
    EXPECT_NEAR(0.08, DecodeOxygenSensorVoltage1("10"), 0.0001);
    EXPECT_NEAR(1.275, DecodeOxygenSensorVoltage1("FF"), 0.0001);
}

TEST(elm327decoders, decodeOxygenSensorVoltage2)
{
    EXPECT_EQ(0, DecodeOxygenSensorVoltage2("0000"));
    EXPECT_NEAR(0.5, DecodeOxygenSensorVoltage2("1000"), 0.0001);
    EXPECT_NEAR(7.9999, DecodeOxygenSensorVoltage2("FFFF"), 0.0001);
}

TEST(elm327decoders, decodePercentage)
{
    EXPECT_EQ(0, DecodePercentage("00"));
    EXPECT_NEAR(16.0784, DecodePercentage("29"), 0.0001);
    EXPECT_EQ(100, DecodePercentage("FF"));
}

TEST(elm327decoders, decodeSignedPercentage)
{
    EXPECT_EQ(-100, DecodeSignedPercentage("00"));
    EXPECT_NEAR(-87.5, DecodeSignedPercentage("10"), 0.01);
    EXPECT_NEAR(99.21, DecodeSignedPercentage("FF"), 0.01);
}

TEST(elm327decoders, decodeRPM)
{
    EXPECT_EQ(0.0, DecodeRPM("0000"));
    EXPECT_EQ(807, DecodeRPM("0C9C"));
    EXPECT_NEAR(16383.75, DecodeRPM("FFFF"), 0.001);
}

TEST(elm327decoders, decodeTemperature)
{
    EXPECT_EQ(-40, DecodeTemperature("00"));
    EXPECT_EQ(1, DecodeTemperature("29"));
    EXPECT_EQ(215, DecodeTemperature("FF"));
}

TEST(elm327decoders, decodeCatalystTemperature)
{
    EXPECT_EQ(-40, DecodeCatalystTemperature("0000"));
    EXPECT_NEAR(369.6, DecodeCatalystTemperature("1000"), 0.0001);
    EXPECT_NEAR(6513.5, DecodeCatalystTemperature("FFFF"), 0.0001);
}

TEST(elm327decoders, decodeTimingAdvance)
{
    EXPECT_EQ(-64, DecodeTimingAdvance("00"));
    EXPECT_NEAR(-56, DecodeTimingAdvance("10"), 0.0001);
    EXPECT_NEAR(63.5, DecodeTimingAdvance("FF"), 0.0001);
}

#endif // DECODERS_TEST_H_