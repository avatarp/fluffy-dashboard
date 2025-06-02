#ifndef LIVE_DATA_TEST_H_
#define LIVE_DATA_TEST_H_

#include "elm327-engine.hpp"
#include <future>
#include <thread>

#include "../common/obd-access-utils.h"
#include "../mocks/obd-access-mock.hpp"
#include <gtest/gtest.h>

using namespace testing;

struct Elm327LiveDataTest : public Test {
    Elm327Engine engine;
    std::shared_ptr<MockUsbAccess> obdAccess;

    void SetUp() override
    {
        obdAccess = std::make_shared<MockUsbAccess>();
        ON_CALL(*obdAccess, IsDeviceFileOk).WillByDefault(Return(true));
        ON_CALL(*obdAccess, OpenConnection).WillByDefault(Return(true));
        engine.SetObdAccess(obdAccess);
    }
};

TEST(Elm327Test, throwOnNoObdAccessSet)
{
    Elm327Engine engine;
    EXPECT_THROW({
        std::ignore = engine.GetObdAccess();
    },
        std::runtime_error);
}

TEST_F(Elm327LiveDataTest, noDeviceOpenConnectionFails)
{
    EXPECT_CALL(*obdAccess, IsDeviceFileOk).WillOnce(Return(false));

    EXPECT_EQ(engine.OpenConnection(), false);

    EXPECT_EQ(engine.GetObdAccess()->GetConnectionStatus(), Obd::ConnectionStatus::DeviceNotFound);
    EXPECT_THROW({ std::ignore = engine.GetObdAccess()->GetDevice(); }, std::runtime_error);
}

TEST_F(Elm327LiveDataTest, dummyUsb)
{
    Obd::Device dummyUsb = CreateUsbDevice();
    engine.GetObdAccess()->SetDevice(dummyUsb);

    EXPECT_TRUE(engine.OpenConnection());
    EXPECT_EQ(engine.GetObdAccess()->GetConnectionStatus(), Obd::ConnectionStatus::Connected);
}

TEST_F(Elm327LiveDataTest, dummyUsbNullCharResponse)
{
    EXPECT_CALL(*obdAccess, Write("0104\r")).WillOnce(Return(false));
    EXPECT_CALL(*obdAccess, Read()).WillOnce(Return(""));

    Obd::Device dummyUsb = CreateUsbDevice();
    engine.GetObdAccess()->SetDevice(dummyUsb);

    auto& actualDevice = engine.GetObdAccess()->GetDevice();
    EXPECT_EQ(actualDevice.m_DeviceFilePath, dummyUsb.m_DeviceFilePath);
    EXPECT_EQ(actualDevice.m_ConnectionType, dummyUsb.m_ConnectionType);
    EXPECT_EQ(actualDevice.m_Description, dummyUsb.m_Description);

    engine.OpenConnection();

    EXPECT_THROW({
        Response response = engine.GetCommandResponse(ObdCommandPid::S01P04);
    },
        std::runtime_error);
}

TEST_F(Elm327LiveDataTest, dummyUsbValidResponse)
{
    EXPECT_CALL(*obdAccess, IsFileDescriptorValid).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, CloseConnection).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Write(_)).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Read()).WillOnce(Return(std::string("7E8 03 41 04 FF")));

    Obd::Device dummyUsb = CreateUsbDevice();
    engine.GetObdAccess()->SetDevice(dummyUsb);

    EXPECT_TRUE(engine.OpenConnection());
    auto response = engine.GetCommandResponse(ObdCommandPid::S01P04);

    EXPECT_EQ("0104", response.m_rawCommandId);
    EXPECT_EQ("7E8", response.m_rawEcuId);
    EXPECT_EQ(3, response.m_rawLength);
    EXPECT_EQ("FF", response.m_rawData);

    EXPECT_TRUE(engine.Disconnect());
}

#endif // LIVE_DATA_TEST_H_
