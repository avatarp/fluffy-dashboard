#ifndef DECODERS_H_
#define DECODERS_H_

#include "Decode.hpp"
#include "DecodeAirFlow.hpp"
#include "DecodeCountA.hpp"
#include "DecodeCountAB.hpp"
#include "DecodeDTC.hpp"
#include "DecodeEquivalenceRatio.hpp"
#include "DecodeEvapPressure.hpp"
#include "DecodeFuelPressure.hpp"
#include "DecodeFuelRailPressure.hpp"
#include "DecodeOxygenSensorCurrent.hpp"
#include "DecodeOxygenSensorVoltage.hpp"
#include "DecodePercentage.hpp"
#include "DecodeRPM.hpp"
#include "DecodeTemperature.hpp"
#include "DecodeTimingAdvance.hpp"
#include <bitset>
#include <optional>

#include <gtest/gtest.h>

using namespace testing;

TEST(elm327decoders, decodeRPM)
{
    DecodeRPM decoder;

    EXPECT_EQ(0.0, decoder.decode("00 00"));
    EXPECT_EQ(807, decoder.decode("0C 9C"));
    EXPECT_NEAR(16383.75, decoder.decode("FF FF"), 0.001);
}

TEST(elm327decoders, decodeSpeed)
{
    DecodeSimpleA decoder;

    EXPECT_EQ(0.0, decoder.decode("00"));
    EXPECT_EQ(17, decoder.decode("11"));
    EXPECT_EQ(255, decoder.decode("FF"));
}

TEST(elm327decoders, decodeTemperature)
{
    DecodeTemperature decoder;

    EXPECT_EQ(-40, decoder.decode("00"));
    EXPECT_EQ(1, decoder.decode("29"));
    EXPECT_EQ(215, decoder.decode("FF"));
}

TEST(elm327decoders, decodePercentage)
{
    DecodePercentage decoder;

    EXPECT_EQ(0, decoder.decode("00"));
    EXPECT_NEAR(16.0784, decoder.decode("29"), 0.0001);
    EXPECT_EQ(100, decoder.decode("FF"));
}

TEST(elm327decoders, decodeAirFlow)
{
    DecodeAirFlow decoder;

    EXPECT_EQ(0, decoder.decode("00 00"));
    EXPECT_NEAR(40.97, decoder.decode("10 01"), 0.0001);
    EXPECT_NEAR(655.35, decoder.decode("FF FF"), 0.0001);
}

TEST(elm327decoders, decodeTimingAdvance)
{
    DecodeTimingAdvance decoder;

    EXPECT_EQ(-64, decoder.decode("00"));
    EXPECT_NEAR(-56, decoder.decode("10"), 0.0001);
    EXPECT_NEAR(63.5, decoder.decode("FF"), 0.0001);
}

TEST(elm327decoders, decodeFuelPressure)
{
    DecodeFuelPressure decoder;

    EXPECT_EQ(0, decoder.decode("00"));
    EXPECT_NEAR(48, decoder.decode("10"), 0.0001);
    EXPECT_NEAR(765, decoder.decode("FF"), 0.0001);
}

TEST(elm327decoders, DecodeCountAB)
{
    DecodeCountAB decoder;

    EXPECT_EQ(0, decoder.decode("00 00"));
    EXPECT_NEAR(4096, decoder.decode("10 00"), 0.0001);
    EXPECT_NEAR(65535, decoder.decode("FF FF"), 0.0001);
}

TEST(elm327decoders, decodeFuelRailPressure)
{
    DecodeFuelRailPressure decoder;

    EXPECT_EQ(0, decoder.decode("00 00"));
    EXPECT_NEAR(323.584, decoder.decode("10 00"), 0.001);
    EXPECT_NEAR(5177.265, decoder.decode("FF FF"), 0.001);
}

TEST(elm327decoders, decodeRunTime)
{
    DecodeFuelRailGaugePressure decoder;

    EXPECT_EQ(0, decoder.decode("00 00"));
    EXPECT_NEAR(40960, decoder.decode("10 00"), 0.0001);
    EXPECT_NEAR(655350, decoder.decode("FF FF"), 0.0001);
}

TEST(elm327decoders, decodeSignedPercentage)
{
    DecodeSignedPercentage decoder;

    EXPECT_EQ(-100, decoder.decode("00"));
    EXPECT_NEAR(-87.5, decoder.decode("10"), 0.01);
    EXPECT_NEAR(99.21, decoder.decode("FF"), 0.01);
}

TEST(elm327decoders, decodeCatalystTemperature)
{
    DecodeCatalystTemperature decoder;

    EXPECT_EQ(-40, decoder.decode("00 00"));
    EXPECT_NEAR(369.6, decoder.decode("10 00"), 0.0001);
    EXPECT_NEAR(6513.5, decoder.decode("FF FF"), 0.0001);
}

TEST(elm327decoders, decodeOxygenSensorVoltage1)
{
    DecodeOxygenSensorVoltage1 decoder;

    EXPECT_EQ(0, decoder.decode("00"));
    EXPECT_NEAR(0.08, decoder.decode("10"), 0.0001);
    EXPECT_NEAR(1.275, decoder.decode("FF"), 0.0001);
}

TEST(elm327decoders, decodeOxygenSensorVoltage2)
{
    DecodeOxygenSensorVoltage2 decoder;

    EXPECT_EQ(0, decoder.decode("00 00"));
    EXPECT_NEAR(0.5, decoder.decode("10 00"), 0.0001);
    EXPECT_NEAR(7.9999, decoder.decode("FF FF"), 0.0001);
}

TEST(elm327decoders, decodeEquivalenceRatio)
{
    DecodeEquivalenceRatio decoder;

    EXPECT_EQ(0, decoder.decode("00 00"));
    EXPECT_NEAR(0.125, decoder.decode("10 00"), 0.0001);
    EXPECT_NEAR(2.0, decoder.decode("FF FF"), 0.0001);
}

TEST(elm327decoders, decodeOxygenSensorCurrent)
{
    DecodeOxygenSensorCurrent decoder;

    EXPECT_NEAR(-128, decoder.decode("00 00"), 0.0001);
    EXPECT_NEAR(-112, decoder.decode("10 00"), 0.0001);
    EXPECT_NEAR(127.996, decoder.decode("FF FF"), 0.0001);
}

TEST(elm327decoders, decodeEvapPressure)
{
    DecodeEvapPressure decoder;

    ASSERT_NEAR(0, decoder.decode("00 00"), 0.0001);
    ASSERT_NEAR(-8192.0, decoder.decode("80 00"), 0.0001);
    ASSERT_NEAR(8191.75, decoder.decode("7F FF"), 0.0001);
}

TEST(elm327decoders, decodeBitEncoded)
{
    DecodeBitEncoded decoder;

    EXPECT_EQ(decoder.decode("00000000"),
        std::bitset<32>(0b00000000000000000000000000000000));

    EXPECT_EQ(decoder.decode("BE1FA813"),
        std::bitset<32>(0b10111110000111111010100000010011));

    EXPECT_EQ(decoder.decode("FFFFFFFF"),
        std::bitset<32>(0b11111111111111111111111111111111));
}

TEST(elm327decoders, decodeString)
{
    DecodeString decoder;

    EXPECT_EQ(decoder.decode(std::string()), "");

    std::string vin = "57463055585847414A5532473830353439";
    EXPECT_EQ(decoder.decode(vin), "WF0UXXGAJU2G80549");
}

TEST(elm327decoders, decodeDTC)
{
    DecodeDTC decoder;

    EXPECT_THROW({
        decoder.decode(std::string());
    },
        std::runtime_error);

    EXPECT_EQ("P0300", decoder.decode("4300"));
    EXPECT_EQ("P0700", decoder.decode("4700"));
}

#endif // DECODERS_H_