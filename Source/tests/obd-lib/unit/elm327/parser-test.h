#ifndef PARSER_TEST_H_
#define PARSER_TEST_H_

#include "elm327-data-parser.hpp"

#include "../common/obd-access-utils.h"
#include <gtest/gtest.h>

using namespace testing;

class elm327Parser_F : public Test {
protected:
    Elm327DataParser parser {};
    Elm327CommandRepository repo{};
    std::string response {};
    ObdCommandPid pid = ObdCommandPid::S01P00;
};

TEST_F(elm327Parser_F, parse0100)
{
    response = "7E8064100983B0011";
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "983B0011");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0100");
    EXPECT_EQ(parsedResponse.m_rawLength, 6);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::bitset);
    EXPECT_EQ(parsedResponse.m_dataBitset, bitset_32(0b10011000001110110000000000010001));
}

TEST_F(elm327Parser_F, parse0100WithSpaces)
{
    response = { "7E8 06 41 00 98 3B 00 11" };
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "983B0011");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0100");
    EXPECT_EQ(parsedResponse.m_rawLength, 6);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::bitset);
    EXPECT_EQ(parsedResponse.m_dataBitset, bitset_32(0b10011000001110110000000000010001));
}

TEST_F(elm327Parser_F, parse0100_expectThrowOnDataLengthMismatch)
{
    response = "7E8064100983B00117E";
    Response thrownResponse;
    EXPECT_THROW(
        {
            thrownResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
        },
        std::runtime_error);

    EXPECT_EQ(thrownResponse.m_dataType, DataType::empty);
    EXPECT_EQ(thrownResponse.m_rawData, "");
    EXPECT_EQ(thrownResponse.m_rawEcuId, "");
    EXPECT_EQ(thrownResponse.m_rawCommandId, "");
    EXPECT_EQ(thrownResponse.m_rawLength, 0);
}

TEST_F(elm327Parser_F, parse0100_NoData)
{
    response = { "NO DATA" };
    Response parsedResponse;

    EXPECT_THROW(
        {
            parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
        },
        std::runtime_error);

    EXPECT_EQ(parsedResponse.m_rawData, "");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "");
    EXPECT_EQ(parsedResponse.m_rawLength, 0);
}

TEST_F(elm327Parser_F, parse0104)
{
    response = { "7E8 03 41 04 FF" };
    pid = ObdCommandPid::S01P04;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "FF");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0104");
    EXPECT_EQ(parsedResponse.m_rawLength, 3);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::number);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 100, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "%");
}

}

TEST_F(elm327Parser_F, parse0900)
{
    response = { "7E8 06 49 00 50 00 00 00" };
    Response parsedResponse = parser.ParseResponse("0900", response, ObdCommandPid::S09P00);
    EXPECT_EQ(parsedResponse.m_rawData, "50000000");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0900");
    EXPECT_EQ(parsedResponse.m_rawLength, 6);
}

#endif // PARSER_TEST_H_
