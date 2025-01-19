#ifndef BLUETOOTH_OBD_ACCESS_TEST_H_
#define BLUETOOTH_OBD_ACCESS_TEST_H_

#include "bluetooth-obd-access.hpp"

#include "../common/obd-access-utils.h"
#include "../mocks/obd-access-mock.hpp"
#include <gtest/gtest.h>

using namespace testing;

class BluetoothAccess_F : public ::testing::Test {
protected:
    MockBtAccess obdAccess {};
};

TEST_F(BluetoothAccess_F, Connect_OpenConnectionFailed)
{
    EXPECT_CALL(obdAccess, IsDeviceFileOk).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, OpenConnection).WillOnce(Return(false));

    ASSERT_FALSE(obdAccess.Connect());
    ASSERT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Disconnected);
}

TEST_F(BluetoothAccess_F, Connect_ApplyDefaultConnectionSettingsFailed)
{
    EXPECT_CALL(obdAccess, IsDeviceFileOk).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, OpenConnection).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, ApplyDefaultConnectionSettings).WillOnce(Return(false));

    ASSERT_FALSE(obdAccess.Connect());
    ASSERT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Disconnected);
}

TEST_F(BluetoothAccess_F, DataTransferOk)
{
    EXPECT_CALL(obdAccess, IsDeviceFileOk).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, OpenConnection).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, ApplyDefaultConnectionSettings).WillOnce(Return(true));
    ASSERT_TRUE(obdAccess.Connect());
    ASSERT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Connected);

    EXPECT_CALL(obdAccess, Transaction("abc")).WillOnce(Return(std::string("def")));
    EXPECT_EQ(obdAccess.Transaction("abc"), "def");

    EXPECT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Connected);
}

TEST_F(BluetoothAccess_F, Reconnect_Default)
{
    EXPECT_CALL(obdAccess, IsDeviceFileOk).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, OpenConnection).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, ApplyDefaultConnectionSettings).WillOnce(Return(true));
    EXPECT_TRUE(obdAccess.Connect());
    EXPECT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Connected);

    EXPECT_CALL(obdAccess, IsFileDescriptorValid).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, Disconnect).WillOnce(Return(true));
    EXPECT_TRUE(obdAccess.CloseConnection());
    EXPECT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Disconnected);

    EXPECT_CALL(obdAccess, IsDeviceFileOk).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, OpenConnection).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, ApplyDefaultConnectionSettings).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, IsFileDescriptorValid).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, Disconnect).WillOnce(Return(true));

    EXPECT_TRUE(obdAccess.Reconnect());
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

#endif // BLUETOOTH_OBD_ACCESS_TEST_H_