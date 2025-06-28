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
    std::shared_ptr<MockUsbAccess> obdAccess;

    void SetUp() override
    {
        obdAccess = std::make_shared<MockUsbAccess>();
        ON_CALL(*obdAccess, IsDeviceFileOk).WillByDefault(Return(true));
        ON_CALL(*obdAccess, OpenConnection).WillByDefault(Return(true));
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

TEST_F(Elm327LiveDataTest, DISABLED_dummyUsbValidMultiFrameVin)
{
    EXPECT_CALL(*obdAccess, IsFileDescriptorValid).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, CloseConnection).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Write(_)).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Read()).WillOnce(Return(std::string("7E8 14 49 02 01 32 54 33")));
    EXPECT_CALL(*obdAccess, Read()).WillOnce(Return(std::string("7E8 52 46 52 45 56 37 44")));
    EXPECT_CALL(*obdAccess, Read()).WillOnce(Return(std::string("7E8 57 31 30 38 31 37 37")));

    Obd::Device dummyUsb = CreateUsbDevice();
    commandProcessor.GetObdAccess()->SetDevice(dummyUsb);

    EXPECT_TRUE(commandProcessor.OpenConnection());
    auto response = commandProcessor.GetCommandResponse(ObdCommandPid::S09P02);

    EXPECT_EQ("0902", response.raw.commandId);
    EXPECT_EQ("7E8", response.raw.ecuId);
    EXPECT_EQ(3, response.raw.length);
    EXPECT_EQ("013254335246524556374457313038313737", response.raw.data);

    EXPECT_TRUE(commandProcessor.Disconnect());
}

#endif // LIVE_DATA_TEST_H_
