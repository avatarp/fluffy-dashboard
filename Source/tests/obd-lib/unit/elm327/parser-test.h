#ifndef PARSER_TEST_H_
#define PARSER_TEST_H_

#include "elm327-data-parser.hpp"

#include "../common/obd-access-utils.h"
#include <gtest/gtest.h>

using namespace testing;

class elm327Parser_F : public Test {
protected:
    Elm327DataParser parser {};
};

TEST_F(elm327Parser_F, parse0100)
{
    std::string response { "7E8 06 41 00 98 3B 00 11" };
    Response parsedResponse = parser.ParseResponse("0100", response, ObdCommandPid::S01P00);
    EXPECT_EQ(parsedResponse.m_rawData, "983B0011");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0100");
    EXPECT_EQ(parsedResponse.m_rawLength, 6);

    response = "7E8064100983B0011";
    parsedResponse = parser.ParseResponse("0100", response, ObdCommandPid::S01P00);
    EXPECT_EQ(parsedResponse.m_rawData, "983B0011");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0100");
    EXPECT_EQ(parsedResponse.m_rawLength, 6);
}

TEST_F(elm327Parser_F, parse0100_expectThrowOnDataLengthMismatch)
{
    std::string response = "7E8064100983B00117E";
    Response thrownResponse;
    EXPECT_THROW(
        {
            thrownResponse = parser.ParseResponse("0100", response, ObdCommandPid::S01P00);
        },
        std::runtime_error);

    EXPECT_EQ(thrownResponse.m_rawData, "");
    EXPECT_EQ(thrownResponse.m_rawEcuId, "");
    EXPECT_EQ(thrownResponse.m_rawCommandId, "");
    EXPECT_EQ(thrownResponse.m_rawLength, 0);
}

TEST_F(elm327Parser_F, parse0100_NoData)
{
    std::string response { "NO DATA" };
    Response parsedResponse;

    EXPECT_THROW(
        {
            parsedResponse = parser.ParseResponse("0100", response, ObdCommandPid::S01P00);
        },
        std::runtime_error);

    EXPECT_EQ(parsedResponse.m_rawData, "");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "");
    EXPECT_EQ(parsedResponse.m_rawLength, 0);
}

TEST_F(elm327Parser_F, parse0104)
{
    std::string response { "7E8 03 41 04 FF" };
    Response parsedResponse = parser.ParseResponse("0104", response, ObdCommandPid::S01P04);
    EXPECT_EQ(parsedResponse.m_rawData, "FF");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0104");
    EXPECT_EQ(parsedResponse.m_rawLength, 3);
}

TEST_F(elm327Parser_F, parse0900)
{
    std::string response { "7E8 06 49 00 50 00 00 00" };
    Response parsedResponse = parser.ParseResponse("0900", response, ObdCommandPid::S0900);
    EXPECT_EQ(parsedResponse.m_rawData, "50000000");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0900");
    EXPECT_EQ(parsedResponse.m_rawLength, 6);
}

#endif // PARSER_TEST_H_
