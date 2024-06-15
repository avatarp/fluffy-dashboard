#ifndef BLUETOOTH_OBD_ACCESS_H_
#define BLUETOOTH_OBD_ACCESS_H_



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
        EXPECT_CALL(obdAccess, Connect).WillOnce(Return(true));
    }
};

TEST_F(BluetoothAccess_F, DataTransferOk)
{
    ASSERT_TRUE(obdAccess.Connect());
    EXPECT_CALL(obdAccess, GetConnectionStatus).WillOnce(Return(Obd::ConnectionStatus::Connected));
    ASSERT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Connected);

    EXPECT_CALL(obdAccess, Transaction("abc")).WillOnce(Return(std::string("def")));
    EXPECT_EQ(obdAccess.Transaction("abc"), "def");

    EXPECT_CALL(obdAccess, GetConnectionStatus).WillOnce(Return(Obd::ConnectionStatus::Connected));
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
    EXPECT_CALL(obdAccess, GetConnectionStatus).WillOnce(Return(Obd::ConnectionStatus::Connected));
    EXPECT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Connected);

    obdAccess.CloseConnection();
    EXPECT_CALL(obdAccess, GetConnectionStatus)
        .WillOnce(Return(Obd::ConnectionStatus::Disconnected));

    EXPECT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Disconnected);

    EXPECT_CALL(obdAccess, Connect()).WillOnce(Return(true));
    EXPECT_TRUE(obdAccess.Connect());
    EXPECT_CALL(obdAccess, GetConnectionStatus).WillOnce(Return(Obd::ConnectionStatus::Connected));
    EXPECT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Connected);

    EXPECT_CALL(obdAccess, Connect()).WillOnce(Return(true));
    EXPECT_TRUE(obdAccess.Reconnect());
    EXPECT_CALL(obdAccess, GetConnectionStatus).WillOnce(Return(Obd::ConnectionStatus::Connected));

    EXPECT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Connected);
}

#endif // BLUETOOTH_OBD_ACCESS_H_