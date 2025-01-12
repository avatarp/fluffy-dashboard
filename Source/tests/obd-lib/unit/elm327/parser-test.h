#ifndef PARSER_TEST_H_
#define PARSER_TEST_H_

#include "elm327-data-parser.hpp"

#include "../common/obd-access-utils.h"
#include <gtest/gtest.h>

using namespace testing;

class elm327Parser_F : public Test {
protected:
    Elm327DataParser parser {};
    Elm327CommandRepository repo {};
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

TEST_F(elm327Parser_F, parse0101)
{
    response = { "7E8 06 41 01 00 66 00 00" };
    pid = ObdCommandPid::S01P01;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "00660000");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0101");
    EXPECT_EQ(parsedResponse.m_rawLength, 6);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::bitset);
    EXPECT_EQ(parsedResponse.m_dataBitset, bitset_32(0x660000));
}

TEST_F(elm327Parser_F, parse0103)
{
    response = { "7E8 04 41 03 02 00" };
    pid = ObdCommandPid::S01P03;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "0200");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0103");
    EXPECT_EQ(parsedResponse.m_rawLength, 4);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::bitset);
    EXPECT_EQ(parsedResponse.m_dataBitset, bitset_32(0x0200));
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

TEST_F(elm327Parser_F, parse0105)
{
    response = { "7E8 03 41 05 4B" };
    pid = ObdCommandPid::S01P05;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "4B");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0105");
    EXPECT_EQ(parsedResponse.m_rawLength, 3);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::number);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 35, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "°C");
}

TEST_F(elm327Parser_F, parse0106)
{
    response = { "7E8 03 41 06 40" };
    pid = ObdCommandPid::S01P06;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "40");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0106");
    EXPECT_EQ(parsedResponse.m_rawLength, 3);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::number);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, -50, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "%");
}

TEST_F(elm327Parser_F, parse0107)
{
    response = { "7E8 03 41 07 41" };
    pid = ObdCommandPid::S01P07;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "41");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0107");
    EXPECT_EQ(parsedResponse.m_rawLength, 3);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::number);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, -49.21875, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "%");
}

TEST_F(elm327Parser_F, parse0108)
{
    response = { "7E8 03 41 08 42" };
    pid = ObdCommandPid::S01P08;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "42");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0108");
    EXPECT_EQ(parsedResponse.m_rawLength, 3);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::number);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, -48.4375, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "%");
}

TEST_F(elm327Parser_F, parse0109)
{
    response = { "7E8 03 41 09 43" };
    pid = ObdCommandPid::S01P09;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "43");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0109");
    EXPECT_EQ(parsedResponse.m_rawLength, 3);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::number);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, -47.65625, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "%");
}

TEST_F(elm327Parser_F, parse010A)
{
    response = { "7E8 03 41 0A 1E" };
    pid = ObdCommandPid::S01P0A;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "1E");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "010A");
    EXPECT_EQ(parsedResponse.m_rawLength, 3);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::number);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 90, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "kPa");
}

TEST_F(elm327Parser_F, parse010B)
{
    response = { "7E8 03 41 0B 0D" };
    pid = ObdCommandPid::S01P0B;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "0D");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "010B");
    EXPECT_EQ(parsedResponse.m_rawLength, 3);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::number);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 13, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "kPa");
}

TEST_F(elm327Parser_F, parse010C)
{
    response = { "7E8 04 41 0C 0C 9C" };
    pid = ObdCommandPid::S01P0C;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "0C9C");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "010C");
    EXPECT_EQ(parsedResponse.m_rawLength, 4);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::number);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 807, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "rpm");
}

TEST_F(elm327Parser_F, parse010D)
{
    response = { "7E8 03 41 0D 10" };
    pid = ObdCommandPid::S01P0D;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "10");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "010D");
    EXPECT_EQ(parsedResponse.m_rawLength, 3);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::number);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 16, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "km/h");
}

TEST_F(elm327Parser_F, parse010E)
{
    response = { "7E8 03 41 0E 12" };
    pid = ObdCommandPid::S01P0E;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "12");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "010E");
    EXPECT_EQ(parsedResponse.m_rawLength, 3);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::number);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, -55, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "° before TDC");
}

TEST_F(elm327Parser_F, parse010F)
{
    response = { "7E8 03 41 0F 52" };
    pid = ObdCommandPid::S01P0F;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "52");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "010F");
    EXPECT_EQ(parsedResponse.m_rawLength, 3);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::number);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 42, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "°C");
}

TEST_F(elm327Parser_F, parse0110)
{
    response = { "7E8 04 41 10 02 F5" };
    pid = ObdCommandPid::S01P10;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "02F5");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0110");
    EXPECT_EQ(parsedResponse.m_rawLength, 4);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::number);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 7.57, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "g/s");
}

TEST_F(elm327Parser_F, parse0111)
{
    response = { "7E8 03 41 11 F6" };
    pid = ObdCommandPid::S01P11;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "F6");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0111");
    EXPECT_EQ(parsedResponse.m_rawLength, 3);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::number);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 96.47, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "%");
}

TEST_F(elm327Parser_F, parse0112)
{
    response = { "7E8 03 41 12 7A" };
    pid = ObdCommandPid::S01P12;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "7A");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0112");
    EXPECT_EQ(parsedResponse.m_rawLength, 3);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::bitset);
    EXPECT_EQ(parsedResponse.m_dataBitset, bitset_32(0x7A));
}

TEST_F(elm327Parser_F, parse0113)
{
    response = { "7E8 03 41 13 4B" };
    pid = ObdCommandPid::S01P13;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "4B");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0113");
    EXPECT_EQ(parsedResponse.m_rawLength, 3);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::bitset);
    EXPECT_EQ(parsedResponse.m_dataBitset, bitset_32(0x4B));
}

TEST_F(elm327Parser_F, parse0114)
{
    response = { "7E8 04 41 14 24 FF" };
    pid = ObdCommandPid::S01P14;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "24FF");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0114");
    EXPECT_EQ(parsedResponse.m_rawLength, 4);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::numberPair);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 0.18, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "V");
    EXPECT_NEAR(parsedResponse.m_dataFloat2.first, 99.21, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat2.second, "%");
}

TEST_F(elm327Parser_F, parse0115)
{
    response = { "7E8 04 41 15 A4 24" };
    pid = ObdCommandPid::S01P15;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "A424");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0115");
    EXPECT_EQ(parsedResponse.m_rawLength, 4);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::numberPair);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 0.81, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "V");
    EXPECT_NEAR(parsedResponse.m_dataFloat2.first, -71.875, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat2.second, "%");
}

TEST_F(elm327Parser_F, parse0116)
{
    response = { "7E8 04 41 16 F0 BB" };
    pid = ObdCommandPid::S01P16;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "F0BB");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0116");
    EXPECT_EQ(parsedResponse.m_rawLength, 4);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::numberPair);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 1.2, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "V");
    EXPECT_NEAR(parsedResponse.m_dataFloat2.first, 46.09, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat2.second, "%");
}

TEST_F(elm327Parser_F, parse0117)
{
    response = { "7E8 04 41 17 23 F0" };
    pid = ObdCommandPid::S01P17;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "23F0");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0117");
    EXPECT_EQ(parsedResponse.m_rawLength, 4);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::numberPair);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 0.175, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "V");
    EXPECT_NEAR(parsedResponse.m_dataFloat2.first, 87.5, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat2.second, "%");
}

TEST_F(elm327Parser_F, parse0118)
{
    response = { "7E8 04 41 18 01 01" };
    pid = ObdCommandPid::S01P18;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "0101");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0118");
    EXPECT_EQ(parsedResponse.m_rawLength, 4);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::numberPair);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 0.005, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "V");
    EXPECT_NEAR(parsedResponse.m_dataFloat2.first, -99.21, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat2.second, "%");
}

TEST_F(elm327Parser_F, parse0119)
{
    response = { "7E8 04 41 19 11 11" };
    pid = ObdCommandPid::S01P19;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "1111");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0119");
    EXPECT_EQ(parsedResponse.m_rawLength, 4);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::numberPair);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 0.085, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "V");
    EXPECT_NEAR(parsedResponse.m_dataFloat2.first, -86.71, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat2.second, "%");
}

TEST_F(elm327Parser_F, parse011A)
{
    response = { "7E8 04 41 1A 22 22" };
    pid = ObdCommandPid::S01P1A;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "2222");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "011A");
    EXPECT_EQ(parsedResponse.m_rawLength, 4);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::numberPair);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 0.17, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "V");
    EXPECT_NEAR(parsedResponse.m_dataFloat2.first, -73.43, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat2.second, "%");
}

TEST_F(elm327Parser_F, parse011B)
{
    response = { "7E8 04 41 1B 33 33" };
    pid = ObdCommandPid::S01P1B;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "3333");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "011B");
    EXPECT_EQ(parsedResponse.m_rawLength, 4);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::numberPair);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 0.255, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "V");
    EXPECT_NEAR(parsedResponse.m_dataFloat2.first, -60.15, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat2.second, "%");
}

TEST_F(elm327Parser_F, parse011C)
{
    response = { "7E8 03 41 1C 06" };
    pid = ObdCommandPid::S01P1C;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "06");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "011C");
    EXPECT_EQ(parsedResponse.m_rawLength, 3);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::bitset);
    EXPECT_EQ(parsedResponse.m_dataBitset, bitset_32(6));
}

TEST_F(elm327Parser_F, parse011D)
{
    response = { "7E8 03 41 1D 9F" };
    pid = ObdCommandPid::S01P1D;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "9F");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "011D");
    EXPECT_EQ(parsedResponse.m_rawLength, 3);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::bitset);
    EXPECT_EQ(parsedResponse.m_dataBitset, bitset_32(0x9F));
}

TEST_F(elm327Parser_F, parse011E)
{
    response = { "7E8 03 41 1E 88" };
    pid = ObdCommandPid::S01P1E;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "88");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "011E");
    EXPECT_EQ(parsedResponse.m_rawLength, 3);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::bitset);
    EXPECT_EQ(parsedResponse.m_dataBitset, bitset_32(0x88));
}

TEST_F(elm327Parser_F, parse011F)
{
    response = { "7E8 04 41 1F 42 11" };
    pid = ObdCommandPid::S01P1F;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "4211");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "011F");
    EXPECT_EQ(parsedResponse.m_rawLength, 4);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::number);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 16913, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "s");
}

TEST_F(elm327Parser_F, parse0120)
{
    response = { "7E8 06 41 20 A0 00 00 00" };
    pid = ObdCommandPid::S01P20;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "A0000000");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0120");
    EXPECT_EQ(parsedResponse.m_rawLength, 6);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::bitset);
    EXPECT_EQ(parsedResponse.m_dataBitset, bitset_32(0xA0000000));
}

TEST_F(elm327Parser_F, parse0123)
{
    response = { "7E8 04 41 23 08 7A" };
    pid = ObdCommandPid::S01P23;
    Response parsedResponse = parser.ParseResponse(repo.getCommandByPid(pid), response, pid);
    EXPECT_EQ(parsedResponse.m_rawData, "087A");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0123");
    EXPECT_EQ(parsedResponse.m_rawLength, 4);

    EXPECT_EQ(parsedResponse.m_dataType, DataType::number);
    EXPECT_NEAR(parsedResponse.m_dataFloat1.first, 21700, 0.01);
    EXPECT_EQ(parsedResponse.m_dataFloat1.second, "kPa");
}

TEST_F(elm327Parser_F, parse0900)
{
    response = { "7E8 06 49 00 50 00 00 00" };
    Response parsedResponse = parser.ParseResponse("0900\r", response, ObdCommandPid::S09P00);
    EXPECT_EQ(parsedResponse.m_rawData, "50000000");
    EXPECT_EQ(parsedResponse.m_rawEcuId, "7E8");
    EXPECT_EQ(parsedResponse.m_rawCommandId, "0900");
    EXPECT_EQ(parsedResponse.m_rawLength, 6);
}

#endif // PARSER_TEST_H_
