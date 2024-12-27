#ifndef LIVE_DATA_TEST_H_
#define LIVE_DATA_TEST_H_

#include "elm327-engine.hpp"
#include <future>
#include <thread>

#include "../common/obd-access-utils.h"
#include "../mocks/obd-access-mock.hpp"
#include <gtest/gtest.h>

using namespace testing;

TEST(elm327LiveData, noDeviceConnection)
{
    Elm327Engine engine;
    EXPECT_EQ(engine.OpenConnection(), false);
}

TEST(elm327LiveData, dummyUsb)
{
    Obd::Device dummyUsb = CreateUsbDevice();
    Elm327Engine engine;
    std::unique_ptr<MockUsbAccess> obdAccess = std::make_unique<MockUsbAccess>();
    EXPECT_CALL(*obdAccess, IsDeviceFileOk).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, OpenConnection).WillOnce(Return(true));
    engine.SetObdAccess(std::move(obdAccess));
    engine.SetSerialDevice(dummyUsb);
    EXPECT_EQ(engine.OpenConnection(), true);
}

TEST(elm327LiveData, dummyUsbNullCharResponse)
{
    std::unique_ptr<MockUsbAccess> obdAccess = std::make_unique<MockUsbAccess>();
    EXPECT_CALL(*obdAccess, IsDeviceFileOk).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, OpenConnection).WillOnce(Return(true));
    EXPECT_CALL(*obdAccess, Write("0104\r")).WillOnce(Return(false));
    EXPECT_CALL(*obdAccess, Read()).WillOnce(Return(""));

    Elm327Engine engine;
    engine.SetObdAccess(std::move(obdAccess));

    Obd::Device dummyUsb = CreateUsbDevice();
    engine.SetSerialDevice(dummyUsb);

    engine.OpenConnection();

    EXPECT_THROW({
        Response response = engine.GetCommandResponse(ObdCommandPid::S01P04);
    },
        std::runtime_error);
}

TEST(elm327LiveData, dummyUsbValidResponse)
{
    std::unique_ptr<MockUsbAccess> mockObd = std::make_unique<MockUsbAccess>();
    EXPECT_CALL(*mockObd, IsDeviceFileOk).WillOnce(Return(true));
    EXPECT_CALL(*mockObd, OpenConnection).WillOnce(Return(true));
    EXPECT_CALL(*mockObd, Write(::testing::_)).WillOnce(Return(true));
    EXPECT_CALL(*mockObd, Read()).WillOnce(Return(std::string("7E8 03 41 04 FF")));

    Obd::Device dummyUsb = CreateUsbDevice();
    Elm327Engine engine;
    engine.SetObdAccess(std::move(mockObd));
    engine.SetSerialDevice(dummyUsb);

    EXPECT_TRUE(engine.OpenConnection());
    auto response = engine.GetCommandResponse(ObdCommandPid::S01P04);

    EXPECT_EQ("0104", response.m_rawCommandId);
    EXPECT_EQ("7E8", response.m_rawEcuId);
    EXPECT_EQ(3, response.m_rawLength);
    EXPECT_EQ("FF", response.m_rawData);
}

#endif // LIVE_DATA_TEST_H_
