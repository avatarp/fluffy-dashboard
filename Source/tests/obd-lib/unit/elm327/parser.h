#ifndef PARSER_H
#define PARSER_H

#include "elm327-data-parser.hpp"

#include "../obd-access-utils.h"
#include <gtest/gtest.h>

using namespace testing;

class elm327Parser_F : public Test {
protected:
    Elm327DataParser parser {};
};

TEST_F(elm327Parser_F, response0100)
{
    std::string response { "7E8 06 41 00 98 3B 00 11" };
    RawResponse parsedResponse = parser.ParseResponse(response, 4, "0100");
    EXPECT_EQ(parsedResponse.m_data, "983B0011");
    EXPECT_EQ(parsedResponse.m_ecuId, "7E8");
    EXPECT_EQ(parsedResponse.m_commandId, "4100");
    EXPECT_EQ(parsedResponse.m_length, 6);

    response = "7E8064100983B0011";
    parsedResponse = parser.ParseResponse(response, 4, "0100");
    EXPECT_EQ(parsedResponse.m_data, "983B0011");
    EXPECT_EQ(parsedResponse.m_ecuId, "7E8");
    EXPECT_EQ(parsedResponse.m_commandId, "4100");
    EXPECT_EQ(parsedResponse.m_length, 6);
}

TEST_F(elm327Parser_F, response0100_NoData)
{
    std::string response { "NO DATA" };
    RawResponse parsedResponse;

    EXPECT_THROW(
        {
            parsedResponse = parser.ParseResponse(response, 4, "0100");
        },
        std::runtime_error);

    EXPECT_EQ(parsedResponse.m_data, "");
    EXPECT_EQ(parsedResponse.m_ecuId, "");
    EXPECT_EQ(parsedResponse.m_commandId, "");
    EXPECT_EQ(parsedResponse.m_length, 0);
}

TEST_F(elm327Parser_F, response0104)
{
    std::string response { "7E8 03 41 04 FF" };
    RawResponse parsedResponse = parser.ParseResponse(response, 1, "0104");
    EXPECT_EQ(parsedResponse.m_data, "FF");
    EXPECT_EQ(parsedResponse.m_ecuId, "7E8");
    EXPECT_EQ(parsedResponse.m_commandId, "4104");
    EXPECT_EQ(parsedResponse.m_length, 3);
}

TEST_F(elm327Parser_F, response0900)
{
    std::string response { "7E8 06 49 00 50 00 00 00" };
    RawResponse parsedResponse = parser.ParseResponse(response, 4, "0900");
    EXPECT_EQ(parsedResponse.m_data, "50000000");
    EXPECT_EQ(parsedResponse.m_ecuId, "7E8");
    EXPECT_EQ(parsedResponse.m_commandId, "4900");
    EXPECT_EQ(parsedResponse.m_length, 6);
}

#endif // PARSER_H
