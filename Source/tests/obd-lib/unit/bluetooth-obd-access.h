#pragma once

#include "bluetooth-obd-access.hpp"

#include <gtest/gtest.h>
#include "mocks/mock-obd-access.hpp"
#include "obd-access-utils.h"

using namespace testing;

class BluetoothAccess_F : public ::testing::Test {
protected:
    MockBtAccess obdAccess;

    void SetUp()
    {
        EXPECT_CALL(obdAccess, IsDeviceFileOk).WillOnce(Return(true));
        EXPECT_CALL(obdAccess, OpenConnection).WillOnce(Return(true));
    }
};

TEST_F(BluetoothAccess_F, DataTransferOk)
{
    ASSERT_TRUE(obdAccess.Connect());
    ASSERT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Connected);

    EXPECT_CALL(obdAccess, Transaction("abc")).WillOnce(Return(std::string("def")));
    EXPECT_EQ(obdAccess.Transaction("abc"), "def");

    EXPECT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Connected);
}

TEST(BluetoothAccess, InvalidDevice)
{
    Obd::BluetoothObdAccess OBD;

    EXPECT_THROW({
        OBD.SetDevice(CreateUsbDevice());
    },
        std::logic_error);
}

TEST(BluetoothAccess, NoDeviceSet)
{
    Obd::BluetoothObdAccess OBD;
    EXPECT_FALSE(OBD.Connect());
    EXPECT_EQ(OBD.GetConnectionStatus(), Obd::ConnectionStatus::DeviceNotFound);
}

TEST(BluetoothAccess, NoDeviceFile)
{
    Obd::BluetoothObdAccess OBD;
    OBD.SetDevice(CreateBluetoothDevice());
    EXPECT_FALSE(OBD.Connect());
    EXPECT_EQ(OBD.GetConnectionStatus(), Obd::ConnectionStatus::DeviceNotFound);
}

TEST_F(BluetoothAccess_F, Reconnect)
{
    EXPECT_TRUE(obdAccess.Connect());
    EXPECT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Connected);

    obdAccess.CloseConnection();
    EXPECT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Disconnected);

    EXPECT_CALL(obdAccess, IsDeviceFileOk).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, OpenConnection).WillOnce(Return(true));

    EXPECT_TRUE(obdAccess.Reconnect());
    EXPECT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Connected);
}
