#ifndef ELM327LIVEDATA_H
#define ELM327LIVEDATA_H

#include "elm327-engine.hpp"
#include <future>
#include <thread>

#include "../mocks/mock-obd-access.hpp"
#include "../obd-access-utils.h"
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

    EXPECT_NEAR(100.0, response.m_floatData1.first, 0.0001);
    EXPECT_EQ("%", response.m_floatData1.second);
    EXPECT_EQ(DataType::number, response.m_dataType);

    EXPECT_EQ("4104", response.m_rawResponse.m_commandId);
    EXPECT_EQ("7E8", response.m_rawResponse.m_ecuId);
    EXPECT_EQ(3, response.m_rawResponse.m_length);
    EXPECT_EQ("FF", response.m_rawResponse.m_data);

    std::clog << "Decoded: "
              << response.m_floatData1.first
              << response.m_floatData1.second << std::endl;
}

#endif // ELM327LIVEDATA_H
