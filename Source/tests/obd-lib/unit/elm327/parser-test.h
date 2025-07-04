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
    ObdCommandPid pid;
    std::string command;

    void SetUp() override
    {
        pid = ObdCommandPid::S01P00;
        command = repo.getCommandByPid(pid);
        // Ensure the command is set correctly for the tests
        if (command.empty()) {
            throw std::runtime_error("Command for PID S01P00 not found in repository.");
        }
    }
};

TEST_F(elm327Parser_F, parse0100)
{
    response = "7E8064100983B0011";
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);
    EXPECT_EQ(parsedResponse.raw.data, "983B0011");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0100");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::bitset);
    EXPECT_EQ(std::get<Bitset_32>(parsedResponse.decodedData), Bitset_32(0b10011000001110110000000000010001));
}

TEST_F(elm327Parser_F, parse0100WithSpaces)
{
    response = { "7E8 06 41 00 98 3B 00 11" };
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);
    EXPECT_EQ(parsedResponse.raw.data, "983B0011");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0100");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::bitset);
    EXPECT_EQ(std::get<Bitset_32>(parsedResponse.decodedData), Bitset_32(0b10011000001110110000000000010001));
}

TEST_F(elm327Parser_F, parse0100_expectThrowOnDataLengthMismatch)
{
    response = "7E8064100983B00117E";
    Response thrownResponse;
    EXPECT_THROW(
        {
            auto data = parser.preProcessResponse(command, response);
            thrownResponse = parser.ParseSingleFrameResponse(command, data.second, pid);
        },
        std::runtime_error);

    EXPECT_EQ(thrownResponse.dataType, DataType::empty);
    EXPECT_EQ(thrownResponse.raw.data, "");
    EXPECT_EQ(thrownResponse.raw.ecuId, "");
    EXPECT_EQ(thrownResponse.raw.commandId, "");
    EXPECT_EQ(thrownResponse.raw.length, 0);
}

TEST_F(elm327Parser_F, parse0100_NoData)
{
    response = { "NO DATA" };
    Response parsedResponse;

    EXPECT_THROW(
        {
            auto data = parser.preProcessResponse(command, response);
            parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);
        },
        std::runtime_error);

    EXPECT_EQ(parsedResponse.raw.data, "");
    EXPECT_EQ(parsedResponse.raw.ecuId, "");
    EXPECT_EQ(parsedResponse.raw.commandId, "");
    EXPECT_EQ(parsedResponse.raw.length, 0);
}

TEST_F(elm327Parser_F, parse0101)
{
    response = { "7E8 06 41 01 00 66 00 00" };
    pid = ObdCommandPid::S01P01;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "00660000");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0101");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::bitset);
    EXPECT_EQ(std::get<Bitset_32>(parsedResponse.decodedData), Bitset_32(0x660000));
}

TEST_F(elm327Parser_F, parse0103)
{
    response = { "7E8 04 41 03 02 00" };
    pid = ObdCommandPid::S01P03;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "0200");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0103");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::bitset);
    EXPECT_EQ(std::get<Bitset_32>(parsedResponse.decodedData), Bitset_32(0x0200));
}

TEST_F(elm327Parser_F, parse0104)
{
    response = { "7E8 03 41 04 FF" };
    pid = ObdCommandPid::S01P04;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "FF");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0104");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 100, 0.01);
    EXPECT_EQ(receivedData.second, "%");
}

TEST_F(elm327Parser_F, parse0105)
{
    response = { "7E8 03 41 05 4B" };
    pid = ObdCommandPid::S01P05;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "4B");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0105");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 35, 0.01);
    EXPECT_EQ(receivedData.second, "°C");
}

TEST_F(elm327Parser_F, parse0106)
{
    response = { "7E8 03 41 06 40" };
    pid = ObdCommandPid::S01P06;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "40");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0106");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, -50, 0.01);
    EXPECT_EQ(receivedData.second, "%");
}

TEST_F(elm327Parser_F, parse0107)
{
    response = { "7E8 03 41 07 41" };
    pid = ObdCommandPid::S01P07;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "41");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0107");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, -49.21875, 0.01);
    EXPECT_EQ(receivedData.second, "%");
}

TEST_F(elm327Parser_F, parse0108)
{
    response = { "7E8 03 41 08 42" };
    pid = ObdCommandPid::S01P08;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "42");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0108");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, -48.4375, 0.01);
    EXPECT_EQ(receivedData.second, "%");
}

TEST_F(elm327Parser_F, parse0109)
{
    response = { "7E8 03 41 09 43" };
    pid = ObdCommandPid::S01P09;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "43");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0109");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, -47.65625, 0.01);
    EXPECT_EQ(receivedData.second, "%");
}

TEST_F(elm327Parser_F, parse010A)
{
    response = { "7E8 03 41 0A 1E" };
    pid = ObdCommandPid::S01P0A;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "1E");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "010A");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 90, 0.01);
    EXPECT_EQ(receivedData.second, "kPa");
}

TEST_F(elm327Parser_F, parse010B)
{
    response = { "7E8 03 41 0B 0D" };
    pid = ObdCommandPid::S01P0B;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "0D");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "010B");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 13, 0.01);
    EXPECT_EQ(receivedData.second, "kPa");
}

TEST_F(elm327Parser_F, parse010C)
{
    response = { "7E8 04 41 0C 0C 9C" };
    pid = ObdCommandPid::S01P0C;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "0C9C");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "010C");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 807, 0.01);
    EXPECT_EQ(receivedData.second, "rpm");
}

TEST_F(elm327Parser_F, parse010D)
{
    response = { "7E8 03 41 0D 10" };
    pid = ObdCommandPid::S01P0D;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "10");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "010D");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 16, 0.01);
    EXPECT_EQ(receivedData.second, "km/h");
}

TEST_F(elm327Parser_F, parse010E)
{
    response = { "7E8 03 41 0E 12" };
    pid = ObdCommandPid::S01P0E;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "12");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "010E");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, -55, 0.01);
    EXPECT_EQ(receivedData.second, "° before TDC");
}

TEST_F(elm327Parser_F, parse010F)
{
    response = { "7E8 03 41 0F 52" };
    pid = ObdCommandPid::S01P0F;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "52");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "010F");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 42, 0.01);
    EXPECT_EQ(receivedData.second, "°C");
}

TEST_F(elm327Parser_F, parse0110)
{
    response = { "7E8 04 41 10 02 F5" };
    pid = ObdCommandPid::S01P10;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "02F5");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0110");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 7.57, 0.01);
    EXPECT_EQ(receivedData.second, "g/s");
}

TEST_F(elm327Parser_F, parse0111)
{
    response = { "7E8 03 41 11 F6" };
    pid = ObdCommandPid::S01P11;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "F6");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0111");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 96.47, 0.01);
    EXPECT_EQ(receivedData.second, "%");
}

TEST_F(elm327Parser_F, parse0112)
{
    response = { "7E8 03 41 12 7A" };
    pid = ObdCommandPid::S01P12;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "7A");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0112");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::bitset);
    EXPECT_EQ(std::get<Bitset_32>(parsedResponse.decodedData), Bitset_32(0x7A));
}

TEST_F(elm327Parser_F, parse0113)
{
    response = { "7E8 03 41 13 4B" };
    pid = ObdCommandPid::S01P13;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "4B");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0113");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::bitset);
    EXPECT_EQ(std::get<Bitset_32>(parsedResponse.decodedData), Bitset_32(0x4B));
}

TEST_F(elm327Parser_F, parse0114)
{
    response = { "7E8 04 41 14 24 FF" };
    pid = ObdCommandPid::S01P14;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "24FF");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0114");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 0.18, 0.01);
    EXPECT_EQ(receivedData.first.second, "V");
    EXPECT_NEAR(receivedData.second.first, 99.21, 0.01);
    EXPECT_EQ(receivedData.second.second, "%");
}

TEST_F(elm327Parser_F, parse0115)
{
    response = { "7E8 04 41 15 A4 24" };
    pid = ObdCommandPid::S01P15;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "A424");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0115");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 0.81, 0.01);
    EXPECT_EQ(receivedData.first.second, "V");
    EXPECT_NEAR(receivedData.second.first, -71.875, 0.01);
    EXPECT_EQ(receivedData.second.second, "%");
}

TEST_F(elm327Parser_F, parse0116)
{
    response = { "7E8 04 41 16 F0 BB" };
    pid = ObdCommandPid::S01P16;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "F0BB");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0116");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 1.2, 0.01);
    EXPECT_EQ(receivedData.first.second, "V");
    EXPECT_NEAR(receivedData.second.first, 46.09, 0.01);
    EXPECT_EQ(receivedData.second.second, "%");
}

TEST_F(elm327Parser_F, parse0117)
{
    response = { "7E8 04 41 17 23 F0" };
    pid = ObdCommandPid::S01P17;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "23F0");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0117");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 0.175, 0.01);
    EXPECT_EQ(receivedData.first.second, "V");
    EXPECT_NEAR(receivedData.second.first, 87.5, 0.01);
    EXPECT_EQ(receivedData.second.second, "%");
}

TEST_F(elm327Parser_F, parse0118)
{
    response = { "7E8 04 41 18 01 01" };
    pid = ObdCommandPid::S01P18;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "0101");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0118");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 0.005, 0.01);
    EXPECT_EQ(receivedData.first.second, "V");
    EXPECT_NEAR(receivedData.second.first, -99.21, 0.01);
    EXPECT_EQ(receivedData.second.second, "%");
}

TEST_F(elm327Parser_F, parse0119)
{
    response = { "7E8 04 41 19 11 11" };
    pid = ObdCommandPid::S01P19;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "1111");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0119");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 0.085, 0.01);
    EXPECT_EQ(receivedData.first.second, "V");
    EXPECT_NEAR(receivedData.second.first, -86.71, 0.01);
    EXPECT_EQ(receivedData.second.second, "%");
}

TEST_F(elm327Parser_F, parse011A)
{
    response = { "7E8 04 41 1A 22 22" };
    pid = ObdCommandPid::S01P1A;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "2222");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "011A");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 0.17, 0.01);
    EXPECT_EQ(receivedData.first.second, "V");
    EXPECT_NEAR(receivedData.second.first, -73.43, 0.01);
    EXPECT_EQ(receivedData.second.second, "%");
}

TEST_F(elm327Parser_F, parse011B)
{
    response = { "7E8 04 41 1B 33 33" };
    pid = ObdCommandPid::S01P1B;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "3333");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "011B");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 0.255, 0.01);
    EXPECT_EQ(receivedData.first.second, "V");
    EXPECT_NEAR(receivedData.second.first, -60.15, 0.01);
    EXPECT_EQ(receivedData.second.second, "%");
}

TEST_F(elm327Parser_F, parse011C)
{
    response = { "7E8 03 41 1C 06" };
    pid = ObdCommandPid::S01P1C;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "06");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "011C");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::bitset);
    EXPECT_EQ(std::get<Bitset_32>(parsedResponse.decodedData), Bitset_32(6));
}

TEST_F(elm327Parser_F, parse011D)
{
    response = { "7E8 03 41 1D 9F" };
    pid = ObdCommandPid::S01P1D;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "9F");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "011D");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::bitset);
    EXPECT_EQ(std::get<Bitset_32>(parsedResponse.decodedData), Bitset_32(0x9F));
}

TEST_F(elm327Parser_F, parse011E)
{
    response = { "7E8 03 41 1E 88" };
    pid = ObdCommandPid::S01P1E;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "88");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "011E");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::bitset);
    EXPECT_EQ(std::get<Bitset_32>(parsedResponse.decodedData), Bitset_32(0x88));
}

TEST_F(elm327Parser_F, parse011F)
{
    response = { "7E8 04 41 1F 42 11" };
    pid = ObdCommandPid::S01P1F;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "4211");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "011F");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 16913, 0.01);
    EXPECT_EQ(receivedData.second, "s");
}

TEST_F(elm327Parser_F, parse0120)
{
    response = { "7E8 06 41 20 A0 00 00 00" };
    pid = ObdCommandPid::S01P20;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "A0000000");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0120");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::bitset);
    EXPECT_EQ(std::get<Bitset_32>(parsedResponse.decodedData), Bitset_32(0xA0000000));
}

TEST_F(elm327Parser_F, parse0121)
{
    response = { "7E8 04 41 21 A0 0B" };
    pid = ObdCommandPid::S01P21;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "A00B");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0121");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 40971, 0.01);
    EXPECT_EQ(receivedData.second, "km");
}

TEST_F(elm327Parser_F, parse0122)
{
    response = { "7E8 04 41 22 0A 11" };
    pid = ObdCommandPid::S01P22;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "0A11");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0122");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 203.583, 0.01);
    EXPECT_EQ(receivedData.second, "kPa");
}

TEST_F(elm327Parser_F, parse0123)
{
    response = { "7E8 04 41 23 08 7A" };
    pid = ObdCommandPid::S01P23;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "087A");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0123");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 21700, 0.01);
    EXPECT_EQ(receivedData.second, "kPa");
}

TEST_F(elm327Parser_F, parse0124)
{
    response = { "7E8 06 41 24 08 7A 0A 11" };
    pid = ObdCommandPid::S01P24;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "087A0A11");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0124");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 0.066223145, 0.0001);
    EXPECT_EQ(receivedData.first.second, "ratio");
    EXPECT_NEAR(receivedData.second.first, 0.314575195, 0.0001);
    EXPECT_EQ(receivedData.second.second, "V");
}

TEST_F(elm327Parser_F, parse0125)
{
    response = { "7E8 06 41 25 A8 BA AA 21" };
    pid = ObdCommandPid::S01P25;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "A8BAAA21");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0125");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 1.31817, 0.0001);
    EXPECT_EQ(receivedData.first.second, "ratio");
    EXPECT_NEAR(receivedData.second.first, 5.3165, 0.0001);
    EXPECT_EQ(receivedData.second.second, "V");
}

TEST_F(elm327Parser_F, parse0126)
{
    response = { "7E8 06 41 26 0A BA 0A 21" };
    pid = ObdCommandPid::S01P26;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "0ABA0A21");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0126");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 0.0838, 0.0001);
    EXPECT_EQ(receivedData.first.second, "ratio");
    EXPECT_NEAR(receivedData.second.first, 0.3165, 0.0001);
    EXPECT_EQ(receivedData.second.second, "V");
}

TEST_F(elm327Parser_F, parse0127)
{
    response = { "7E8 06 41 27 AA BA BB 21" };
    pid = ObdCommandPid::S01P27;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "AABABB21");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0127");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 1.3338, 0.0001);
    EXPECT_EQ(receivedData.first.second, "ratio");
    EXPECT_NEAR(receivedData.second.first, 5.8477, 0.0001);
    EXPECT_EQ(receivedData.second.second, "V");
}

TEST_F(elm327Parser_F, parse0128)
{
    response = { "7E8 06 41 28 FF 00 FF 00" };
    pid = ObdCommandPid::S01P28;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "FF00FF00");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0128");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 1.9921, 0.0001);
    EXPECT_EQ(receivedData.first.second, "ratio");
    EXPECT_NEAR(receivedData.second.first, 7.9687, 0.0001);
    EXPECT_EQ(receivedData.second.second, "V");
}

TEST_F(elm327Parser_F, parse0129)
{
    response = { "7E8 06 41 29 00 FF 00 FF" };
    pid = ObdCommandPid::S01P29;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "00FF00FF");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0129");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 0.0077, 0.0001);
    EXPECT_EQ(receivedData.first.second, "ratio");
    EXPECT_NEAR(receivedData.second.first, 0.0311, 0.0001);
    EXPECT_EQ(receivedData.second.second, "V");
}

TEST_F(elm327Parser_F, parse012A)
{
    response = { "7E8 06 41 2A 0A BA 0A 21" };
    pid = ObdCommandPid::S01P2A;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "0ABA0A21");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "012A");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 0.0838, 0.0001);
    EXPECT_EQ(receivedData.first.second, "ratio");
    EXPECT_NEAR(receivedData.second.first, 0.3165, 0.0001);
    EXPECT_EQ(receivedData.second.second, "V");
}

TEST_F(elm327Parser_F, parse012B)
{
    response = { "7E8 06 41 2B 99 99 99 99" };
    pid = ObdCommandPid::S01P2B;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "99999999");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "012B");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 1.1999, 0.0001);
    EXPECT_EQ(receivedData.first.second, "ratio");
    EXPECT_NEAR(receivedData.second.first, 4.7999, 0.0001);
    EXPECT_EQ(receivedData.second.second, "V");
}

TEST_F(elm327Parser_F, parse012C)
{
    response = { "7E8 03 41 2C BE" };
    pid = ObdCommandPid::S01P2C;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "BE");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "012C");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 74.50, 0.01);
    EXPECT_EQ(receivedData.second, "%");
}

TEST_F(elm327Parser_F, parse012D)
{
    response = { "7E8 03 41 2D FE" };
    pid = ObdCommandPid::S01P2D;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "FE");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "012D");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 98.43, 0.01);
    EXPECT_EQ(receivedData.second, "%");
}

TEST_F(elm327Parser_F, parse012E)
{
    response = { "7E8 03 41 2E 2E" };
    pid = ObdCommandPid::S01P2E;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "2E");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "012E");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 18.03, 0.01);
    EXPECT_EQ(receivedData.second, "%");
}

TEST_F(elm327Parser_F, parse012F)
{
    response = { "7E8 03 41 2F 11" };
    pid = ObdCommandPid::S01P2F;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "11");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "012F");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 6.66, 0.01);
    EXPECT_EQ(receivedData.second, "%");
}

TEST_F(elm327Parser_F, parse0130)
{
    response = { "7E8 03 41 30 13" };
    pid = ObdCommandPid::S01P30;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "13");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0130");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 19, 0.01);
    EXPECT_EQ(receivedData.second, "count");
}

TEST_F(elm327Parser_F, parse0131)
{
    response = { "7E8 04 41 31 33 01" };
    pid = ObdCommandPid::S01P31;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "3301");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0131");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 13057, 0.01);
    EXPECT_EQ(receivedData.second, "km");
}

TEST_F(elm327Parser_F, parse0132)
{
    response = { "7E8 04 41 32 33 33" };
    pid = ObdCommandPid::S01P32;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "3333");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0132");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 3276.75, 0.01);
    EXPECT_EQ(receivedData.second, "Pa");
}

TEST_F(elm327Parser_F, parse0133)
{
    response = { "7E8 03 41 33 88" };
    pid = ObdCommandPid::S01P33;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "88");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0133");
    EXPECT_EQ(parsedResponse.raw.length, 3);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 136, 0.01);
    EXPECT_EQ(receivedData.second, "kPa");
}

TEST_F(elm327Parser_F, parse0134)
{
    response = { "7E8 06 41 34 33 33 AB BA" };
    pid = ObdCommandPid::S01P34;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "3333ABBA");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0134");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 0.399993896, 0.001);
    EXPECT_EQ(receivedData.first.second, "ratio");
    EXPECT_NEAR(receivedData.second.first, 43.7265625, 0.001);
    EXPECT_EQ(receivedData.second.second, "mA");
}

TEST_F(elm327Parser_F, parse0135)
{
    response = { "7E8 06 41 35 AB BA BA BA" };
    pid = ObdCommandPid::S01P35;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "ABBABABA");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0135");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 1.34161376, 0.001);
    EXPECT_EQ(receivedData.first.second, "ratio");
    EXPECT_NEAR(receivedData.second.first, 58.7265625, 0.001);
    EXPECT_EQ(receivedData.second.second, "mA");
}

TEST_F(elm327Parser_F, parse0136)
{
    response = { "7E8 06 41 36 00 33 00 BA" };
    pid = ObdCommandPid::S01P36;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "003300BA");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0136");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 0.00155639, 0.001);
    EXPECT_EQ(receivedData.first.second, "ratio");
    EXPECT_NEAR(receivedData.second.first, -127.2734375, 0.001);
    EXPECT_EQ(receivedData.second.second, "mA");
}

TEST_F(elm327Parser_F, parse0137)
{
    response = { "7E8 06 41 37 40 00 40 00" };
    pid = ObdCommandPid::S01P37;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "40004000");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0137");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 0.5000, 0.001);
    EXPECT_EQ(receivedData.first.second, "ratio");
    EXPECT_NEAR(receivedData.second.first, -64.000, 0.001);
    EXPECT_EQ(receivedData.second.second, "mA");
}

TEST_F(elm327Parser_F, parse0138)
{
    response = { "7E8 06 41 38 00 00 00 00" };
    pid = ObdCommandPid::S01P38;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "00000000");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0138");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 0.000, 0.001);
    EXPECT_EQ(receivedData.first.second, "ratio");
    EXPECT_NEAR(receivedData.second.first, -128.000, 0.001);
    EXPECT_EQ(receivedData.second.second, "mA");
}

TEST_F(elm327Parser_F, parse0139)
{
    response = { "7E8 06 41 39 FF FF FF FF" };
    pid = ObdCommandPid::S01P39;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "FFFFFFFF");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "0139");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 2.000, 0.001);
    EXPECT_EQ(receivedData.first.second, "ratio");
    EXPECT_NEAR(receivedData.second.first, 127.996, 0.001);
    EXPECT_EQ(receivedData.second.second, "mA");
}

TEST_F(elm327Parser_F, parse013A)
{
    response = { "7E8 06 41 3A 33 33 AB BA" };
    pid = ObdCommandPid::S01P3A;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "3333ABBA");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "013A");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 0.399993896, 0.001);
    EXPECT_EQ(receivedData.first.second, "ratio");
    EXPECT_NEAR(receivedData.second.first, 43.7265625, 0.001);
    EXPECT_EQ(receivedData.second.second, "mA");
}

TEST_F(elm327Parser_F, parse013B)
{
    response = { "7E8 06 41 3B 33 33 AB BA" };
    pid = ObdCommandPid::S01P3B;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "3333ABBA");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "013B");
    EXPECT_EQ(parsedResponse.raw.length, 6);

    EXPECT_EQ(parsedResponse.dataType, DataType::numberPair);
    auto receivedData = std::get<FloatDataPair>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first.first, 0.399993896, 0.001);
    EXPECT_EQ(receivedData.first.second, "ratio");
    EXPECT_NEAR(receivedData.second.first, 43.7265625, 0.001);
    EXPECT_EQ(receivedData.second.second, "mA");
}

TEST_F(elm327Parser_F, parse013C)
{
    response = { "7E8 04 41 3C 69 96" };
    pid = ObdCommandPid::S01P3C;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "6996");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "013C");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 2663, 0.01);
    EXPECT_EQ(receivedData.second, "°C");
}

TEST_F(elm327Parser_F, parse013D)
{
    response = { "7E8 04 41 3D 00 00" };
    pid = ObdCommandPid::S01P3D;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "0000");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "013D");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, -40, 0.01);
    EXPECT_EQ(receivedData.second, "°C");
}

TEST_F(elm327Parser_F, parse013E)
{
    response = { "7E8 04 41 3E FF FF" };
    pid = ObdCommandPid::S01P3E;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "FFFF");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "013E");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 6513.5, 0.01);
    EXPECT_EQ(receivedData.second, "°C");
}

TEST_F(elm327Parser_F, parse013F)
{
    response = { "7E8 04 41 3F 80 80" };
    pid = ObdCommandPid::S01P3F;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    EXPECT_EQ(parsedResponse.raw.data, "8080");
    EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    EXPECT_EQ(parsedResponse.raw.commandId, "013F");
    EXPECT_EQ(parsedResponse.raw.length, 4);

    EXPECT_EQ(parsedResponse.dataType, DataType::number);
    auto receivedData = std::get<FloatData>(parsedResponse.decodedData);
    EXPECT_NEAR(receivedData.first, 3249.60, 0.01);
    EXPECT_EQ(receivedData.second, "°C");
}

TEST_F(elm327Parser_F, parse0900)
{
    response = { "7E8 06 49 00 50 00 00 00" };
    pid = ObdCommandPid::S09P00;
    command = repo.getCommandByPid(pid);
    auto data = parser.preProcessResponse(command, response);
    // Response parsedResponse = parser.ParseSingleFrameResponse(command, data.second, pid);

    // EXPECT_EQ(parsedResponse.raw.data, "50000000");
    // EXPECT_EQ(parsedResponse.raw.ecuId, "7E8");
    // EXPECT_EQ(parsedResponse.raw.commandId, "0900");
    // EXPECT_EQ(parsedResponse.raw.length, 6);
}

#endif // PARSER_TEST_H_
