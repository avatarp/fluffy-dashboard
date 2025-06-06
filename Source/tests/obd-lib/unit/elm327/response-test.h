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
    resp.dataType = DataType::string;
    resp.decodedData = StringData { "Hello", "World" };
    oss << resp;
    EXPECT_EQ(oss.str(), "string: Hello, World\n");
}

TEST_F(ResponseTest, NumberDataType)
{
    resp.dataType = DataType::number;
    resp.decodedData = FloatData { 100.0f, "%" };
    oss << resp;
    EXPECT_EQ(oss.str(), "float: 100%\n");
}

TEST_F(ResponseTest, NumberPairDataType)
{
    resp.dataType = DataType::numberPair;
    resp.decodedData = FloatDataPair({ 1.23f, "V" }, { 7.89f, "%" });
    oss << resp;
    EXPECT_EQ(oss.str(), "float pair: 1.23V, 7.89%\n");
}

TEST_F(ResponseTest, DtcDataType)
{
    resp.dataType = DataType::dtc;
    resp.decodedData = StringData { "P0123", "Throttle Position Sensor" };
    oss << resp;
    EXPECT_EQ(oss.str(), "dtc string: P0123, Throttle Position Sensor\n");
}

TEST_F(ResponseTest, BitsetDataType)
{
    resp.dataType = DataType::bitset;
    resp.decodedData = Bitset_32(0b10101010101010101010101010101010);
    oss << resp;
    EXPECT_EQ(oss.str(), "bitset: 10101010101010101010101010101010\n");
}

TEST_F(ResponseTest, DefaultDataType)
{
    constexpr int invalidDataType = -1;
    resp.dataType = static_cast<DataType>(invalidDataType);
    oss << resp;
    EXPECT_EQ(oss.str(), "Empty response\n");
}

#endif // RESPONSE_TEST_H_