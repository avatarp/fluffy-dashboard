#ifndef LIVE_DATA_TEST_H_
#define LIVE_DATA_TEST_H_

#include "elm327-command-processor.hpp"
#include <future>
#include <thread>

#include "../common/obd-access-utils.h"
#include "../mocks/obd-access-mock.hpp"
#include <gtest/gtest.h>

using namespace testing;

struct Elm327LiveDataTest : public Test {
    Elm327CommandProcessor commandProcessor;
    std::shared_ptr<NiceMock<MockUsbAccess>> obdAccess;

    void SetUp() override
    {
        obdAccess = std::make_shared<NiceMock<MockUsbAccess>>();
        EXPECT_CALL(*obdAccess, IsDeviceFileOk).WillRepeatedly(Return(true));
        EXPECT_CALL(*obdAccess, OpenConnection).WillRepeatedly(Return(true));
        commandProcessor.SetObdAccess(obdAccess);
    }
};

TEST(Elm327Test, throwOnNoObdAccessSet)
{
    Elm327CommandProcessor processor;
    EXPECT_THROW({
        std::ignore = processor.GetObdAccess();
    },
        std::runtime_error);
}

TEST_F(Elm327LiveDataTest, throwOnSendCommandFailure)
{
    obdAccess->SetDevice(CreateUsbDevice());
    EXPECT_CALL(*obdAccess, Write(_)).WillOnce(Return(false));

    EXPECT_THROW({
        std::ignore = commandProcessor.GetCommandResponse(ObdCommandPid::S01P04);
    },
        std::runtime_error);
}

TEST_F(Elm327LiveDataTest, noDeviceOpenConnectionFails)
{
    EXPECT_CALL(*obdAccess, IsDeviceFileOk).WillOnce(Return(false));

    EXPECT_EQ(commandProcessor.OpenConnection(), false);

    EXPECT_EQ(commandProcessor.GetObdAccess()->GetConnectionStatus(), Obd::ConnectionStatus::DeviceNotFound);
    EXPECT_THROW({ std::ignore = commandProcessor.GetObdAccess()->GetDevice(); }, std::runtime_error);
}

TEST_F(Elm327LiveDataTest, dummyUsb)
{
    Obd::Device dummyUsb = CreateUsbDevice();
    commandProcessor.GetObdAccess()->SetDevice(dummyUsb);

    EXPECT_TRUE(commandProcessor.OpenConnection());
    EXPECT_EQ(commandProcessor.GetObdAccess()->GetConnectionStatus(), Obd::ConnectionStatus::Connected);
}

TEST_F(Elm327LiveDataTest, dummyUsbNullCharResponse)
{
    Obd::Device dummyUsb = CreateUsbDevice();
    commandProcessor.GetObdAccess()->SetDevice(dummyUsb);

    auto& actualDevice = commandProcessor.GetObdAccess()->GetDevice();
    EXPECT_EQ(actualDevice.m_DeviceFilePath, dummyUsb.m_DeviceFilePath);
    EXPECT_EQ(actualDevice.m_ConnectionType, dummyUsb.m_ConnectionType);
    EXPECT_EQ(actualDevice.m_Description, dummyUsb.m_Description);

    commandProcessor.OpenConnection();

    EXPECT_CALL(*obdAccess, Write("0104\r")).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Read()).WillOnce(Return(""));

    EXPECT_THROW({
        Response response = commandProcessor.GetCommandResponse(ObdCommandPid::S01P04);
    },
        std::runtime_error);
}

TEST_F(Elm327LiveDataTest, dummyUsbValidSingleFrame)
{
    EXPECT_CALL(*obdAccess, IsFileDescriptorValid).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, CloseConnection).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Write(_)).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Read()).WillOnce(Return(std::string("7E8 03 41 04 FF")));

    Obd::Device dummyUsb = CreateUsbDevice();
    commandProcessor.GetObdAccess()->SetDevice(dummyUsb);

    EXPECT_TRUE(commandProcessor.OpenConnection());
    auto response = commandProcessor.GetCommandResponse(ObdCommandPid::S01P04);

    EXPECT_EQ("0104", response.raw.commandId);
    EXPECT_EQ("7E8", response.raw.ecuId);
    EXPECT_EQ(3, response.raw.length);
    EXPECT_EQ("FF", response.raw.data);

    EXPECT_TRUE(commandProcessor.Disconnect());
}

TEST_F(Elm327LiveDataTest, dummyUsbValidSingleFrameDtc)
{
    EXPECT_CALL(*obdAccess, IsFileDescriptorValid).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, CloseConnection).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Write("03\r")).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Read()).WillOnce(Return(std::string("7E8 04 43 01 04 20")));

    Obd::Device dummyUsb = CreateUsbDevice();
    commandProcessor.GetObdAccess()->SetDevice(dummyUsb);

    EXPECT_TRUE(commandProcessor.OpenConnection());
    auto response = commandProcessor.GetCommandResponse(ObdCommandPid::S03);

    EXPECT_EQ("03", response.raw.commandId);
    EXPECT_EQ("7E8", response.raw.ecuId);
    EXPECT_EQ(4, response.raw.length);
    EXPECT_EQ("010420", response.raw.data);

    auto storedDtcCodes = commandProcessor.GetDtcHandler()->GetStoredDtcCodes();
    EXPECT_EQ(storedDtcCodes.size(), 1);
    EXPECT_EQ(storedDtcCodes[0], "P0420");

    EXPECT_TRUE(commandProcessor.Disconnect());
}

TEST_F(Elm327LiveDataTest, dummyUsbValidSingleFrameDtc2)
{
    EXPECT_CALL(*obdAccess, IsFileDescriptorValid).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, CloseConnection).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Write("03\r")).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Read()).WillOnce(Return(std::string("7E8 06 43 02 04 20 B1 10")));

    Obd::Device dummyUsb = CreateUsbDevice();
    commandProcessor.GetObdAccess()->SetDevice(dummyUsb);

    EXPECT_TRUE(commandProcessor.OpenConnection());
    auto response = commandProcessor.GetCommandResponse(ObdCommandPid::S03);

    EXPECT_EQ("03", response.raw.commandId);
    EXPECT_EQ("7E8", response.raw.ecuId);
    EXPECT_EQ(6, response.raw.length);
    EXPECT_EQ("020420B110", response.raw.data);

    auto storedDtcCodes = commandProcessor.GetDtcHandler()->GetStoredDtcCodes();
    EXPECT_EQ(storedDtcCodes.size(), 2);
    EXPECT_EQ(storedDtcCodes[0], "P0420");
    EXPECT_EQ(storedDtcCodes[1], "B3110");

    EXPECT_TRUE(commandProcessor.Disconnect());
}

TEST_F(Elm327LiveDataTest, dummyUsbValidMultiFrameDtc3)
{
    EXPECT_CALL(*obdAccess, IsFileDescriptorValid).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, CloseConnection).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Write("07\r")).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Write("3101F1\r")).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Read())
        .WillOnce(Return(std::string("7E8 10 08 47 03 04 20 B1 10 43")))
        .WillOnce(Return(std::string("7E8 21 00")));

    Obd::Device dummyUsb = CreateUsbDevice();
    commandProcessor.GetObdAccess()->SetDevice(dummyUsb);

    EXPECT_TRUE(commandProcessor.OpenConnection());
    auto response = commandProcessor.GetCommandResponse(ObdCommandPid::S07);

    EXPECT_EQ("07", response.raw.commandId);
    EXPECT_EQ("7E8", response.raw.ecuId);
    EXPECT_EQ(8, response.raw.length);
    EXPECT_EQ("030420B1104300", response.raw.data);

    auto pendingDtcCodes = commandProcessor.GetDtcHandler()->GetPendingDtcCodes();
    EXPECT_EQ(pendingDtcCodes.size(), 3);
    EXPECT_EQ(pendingDtcCodes[0], "P0420");
    EXPECT_EQ(pendingDtcCodes[1], "B3110");
    EXPECT_EQ(pendingDtcCodes[2], "C0300");

    EXPECT_TRUE(commandProcessor.Disconnect());
}

TEST_F(Elm327LiveDataTest, dummyUsbValidMultiFrameDtc4)
{
    EXPECT_CALL(*obdAccess, IsFileDescriptorValid).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, CloseConnection).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Write("0A\r")).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Write("3101F1\r")).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Read())
        .WillOnce(Return(std::string("7E8 10 0A 4A 04 04 20 B1 10 43")))
        .WillOnce(Return(std::string("7E8 21 00 32 23")));

    Obd::Device dummyUsb = CreateUsbDevice();
    commandProcessor.GetObdAccess()->SetDevice(dummyUsb);

    EXPECT_TRUE(commandProcessor.OpenConnection());
    auto response = commandProcessor.GetCommandResponse(ObdCommandPid::S0A);

    EXPECT_EQ("0A", response.raw.commandId);
    EXPECT_EQ("7E8", response.raw.ecuId);
    EXPECT_EQ(10, response.raw.length);
    EXPECT_EQ("040420B11043003223", response.raw.data);

    auto permanentDtcCodes = commandProcessor.GetDtcHandler()->GetPermanentDtcCodes();
    EXPECT_EQ(permanentDtcCodes.size(), 4);
    EXPECT_EQ(permanentDtcCodes[0], "P0420");
    EXPECT_EQ(permanentDtcCodes[1], "B3110");
    EXPECT_EQ(permanentDtcCodes[2], "C0300");
    EXPECT_EQ(permanentDtcCodes[3], "P3223");

    EXPECT_TRUE(commandProcessor.Disconnect());
}

TEST_F(Elm327LiveDataTest, dummyUsbValidConsecutiveFrameFirst)
{
    EXPECT_CALL(*obdAccess, Write(_)).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Read()).WillOnce(Return(std::string("7E8 23 41 04 FF")));

    Obd::Device dummyUsb = CreateUsbDevice();
    commandProcessor.GetObdAccess()->SetDevice(dummyUsb);

    EXPECT_TRUE(commandProcessor.OpenConnection());
    EXPECT_THROW({
        std::ignore = commandProcessor.GetCommandResponse(ObdCommandPid::S01P04);
    },
        std::runtime_error);
}

TEST_F(Elm327LiveDataTest, dummyUsbValidInvalidFrameFirst)
{
    EXPECT_CALL(*obdAccess, Write(_)).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Read()).WillOnce(Return(std::string("7E8 F3 41 04 FF")));

    Obd::Device dummyUsb = CreateUsbDevice();
    commandProcessor.GetObdAccess()->SetDevice(dummyUsb);

    EXPECT_TRUE(commandProcessor.OpenConnection());
    EXPECT_THROW({
        std::ignore = commandProcessor.GetCommandResponse(ObdCommandPid::S01P04);
    },
        std::runtime_error);
}

TEST_F(Elm327LiveDataTest, dummyUsbValidMultiFrameVin)
{
    EXPECT_CALL(*obdAccess, IsFileDescriptorValid).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, CloseConnection).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Write("0902\r")).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Write("3101F1\r")).Times(2).WillRepeatedly(Return(true));
    EXPECT_CALL(*obdAccess, Read())
        .WillOnce(Return(std::string("7E8 10 14 49 02 01 32 54 33")))
        .WillOnce(Return(std::string("7E8 21 52 46 52 45 56 37 44")))
        .WillOnce(Return(std::string("7E8 22 57 31 30 38 31 37 37")));

    Obd::Device dummyUsb = CreateUsbDevice();
    commandProcessor.GetObdAccess()->SetDevice(dummyUsb);

    EXPECT_TRUE(commandProcessor.OpenConnection());
    auto response = commandProcessor.GetCommandResponse(ObdCommandPid::S09P02);

    EXPECT_EQ("0902", response.raw.commandId);
    EXPECT_EQ("7E8", response.raw.ecuId);
    EXPECT_EQ(20, response.raw.length);
    EXPECT_EQ("013254335246524556374457313038313737", response.raw.data);

    EXPECT_EQ("2T3RFREV7DW108177", std::get<StringData>(response.decodedData).first);

    EXPECT_TRUE(commandProcessor.Disconnect());
}

TEST_F(Elm327LiveDataTest, dummyUsbValidMultiFrameVinFailInvalidFrameType)
{
    EXPECT_CALL(*obdAccess, Write("0902\r")).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Write("3101F1\r")).Times(2).WillRepeatedly(Return(true));
    EXPECT_CALL(*obdAccess, Read())
        .WillOnce(Return(std::string("7E8 10 14 49 02 01 32 54 33")))
        .WillOnce(Return(std::string("7E8 21 52 46 52 45 56 37 44")))
        .WillOnce(Return(std::string("7E8 32 57 31 30 38 31 37 37")));

    Obd::Device dummyUsb = CreateUsbDevice();
    commandProcessor.GetObdAccess()->SetDevice(dummyUsb);

    EXPECT_TRUE(commandProcessor.OpenConnection());
    EXPECT_THROW({
        std::ignore = commandProcessor.GetCommandResponse(ObdCommandPid::S09P02);
    },
        std::runtime_error);
}

TEST_F(Elm327LiveDataTest, dummyUsbValidMultiFrameVinFailEmptyFrame)
{
    EXPECT_CALL(*obdAccess, Write("0902\r")).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Write("3101F1\r")).Times(2).WillRepeatedly(Return(true));
    EXPECT_CALL(*obdAccess, Read())
        .WillOnce(Return(std::string("7E8 10 14 49 02 01 32 54 33")))
        .WillOnce(Return(std::string("7E8 21 52 46 52 45 56 37 44")))
        .WillOnce(Return(std::string("  ")));

    Obd::Device dummyUsb = CreateUsbDevice();
    commandProcessor.GetObdAccess()->SetDevice(dummyUsb);

    EXPECT_TRUE(commandProcessor.OpenConnection());
    EXPECT_THROW({
        std::ignore = commandProcessor.GetCommandResponse(ObdCommandPid::S09P02);
    },
        std::runtime_error);
}

TEST_F(Elm327LiveDataTest, dummyUsbValidMultiFrameVinFailToSendFlowControlCommand)
{
    EXPECT_CALL(*obdAccess, Write("0902\r")).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Write("3101F1\r")).WillOnce(Return(true)).WillOnce(Return(false));
    EXPECT_CALL(*obdAccess, Read())
        .WillOnce(Return(std::string("7E8 10 14 49 02 01 32 54 33")))
        .WillOnce(Return(std::string("7E8 21 52 46 52 45 56 37 44")));

    Obd::Device dummyUsb = CreateUsbDevice();
    commandProcessor.GetObdAccess()->SetDevice(dummyUsb);

    EXPECT_TRUE(commandProcessor.OpenConnection());
    EXPECT_THROW({
        std::ignore = commandProcessor.GetCommandResponse(ObdCommandPid::S09P02);
    },
        std::runtime_error);
}
#endif // LIVE_DATA_TEST_H_
