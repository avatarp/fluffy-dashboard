#ifndef RESPONSE_TEST_H_
#define RESPONSE_TEST_H_

#include "response.hpp"
#include <gtest/gtest.h>
#include <sstream>

class ResponseTest : public ::testing::Test {
protected:
    Response resp;
    std::ostringstream oss;
};

TEST_F(ResponseTest, StringDataType)
{
    resp.m_dataType = DataType::string;
    resp.m_dataString = { "Hello", "World" };
    oss << resp;
    EXPECT_EQ(oss.str(), "string: Hello, World\n");
}

TEST_F(ResponseTest, NumberDataType)
{
    resp.m_dataType = DataType::number;
    resp.m_dataFloat1 = { 100.0f, "%" };
    oss << resp;
    EXPECT_EQ(oss.str(), "float: 100%\n");
}

TEST_F(ResponseTest, NumberPairDataType)
{
    resp.m_dataType = DataType::numberPair;
    resp.m_dataFloat1 = { 1.23f, "V" };
    resp.m_dataFloat2 = { 7.89f, "%" };
    oss << resp;
    EXPECT_EQ(oss.str(), "float pair: 1.23V, 7.89%\n");
}

TEST_F(ResponseTest, DtcDataType)
{
    resp.m_dataType = DataType::dtc;
    resp.m_dataString = { "P0123", "Throttle Position Sensor" };
    oss << resp;
    EXPECT_EQ(oss.str(), "dtc string: P0123, Throttle Position Sensor\n");
}

TEST_F(ResponseTest, BitsetDataType)
{
    resp.m_dataType = DataType::bitset;
    resp.m_dataBitset = bitset_32(0b10101010101010101010101010101010);
    oss << resp;
    EXPECT_EQ(oss.str(), "bitset: 10101010101010101010101010101010\n");
}

TEST_F(ResponseTest, DefaultDataType)
{
    constexpr int invalidDataType = -1;
    resp.m_dataType = static_cast<DataType>(invalidDataType);
    oss << resp;
    EXPECT_EQ(oss.str(), "Empty response\n");
}

#endif // RESPONSE_TEST_H_