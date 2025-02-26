#ifndef SERIAL_OBD_ACCESS_TEST_H_
#define SERIAL_OBD_ACCESS_TEST_H_

#include "serial-obd-access.hpp"

#include "../../common/obd-access-utils.h"
#include "../../mocks/obd-access-mock.hpp"
#include "../../mocks/obd-device-mock.hpp"
#include <gtest/gtest.h>

using namespace testing;

class UsbAccess_F : public ::testing::Test {
protected:
    MockUsbAccess obdAccess {};
};

TEST(UsbAccess, WriteOnNoConnectionFailed)
{
    Obd::UsbObdAccess usbAccess;
    EXPECT_FALSE(usbAccess.Write(""));
}

TEST_F(UsbAccess_F, Connect_OpenConnectionFailed)
{
    EXPECT_CALL(obdAccess, IsDeviceFileOk).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, OpenConnection).WillOnce(Return(false));

    ASSERT_FALSE(obdAccess.Connect());
    ASSERT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Disconnected);
}

TEST_F(UsbAccess_F, DataTransferOk)
{
    EXPECT_CALL(obdAccess, IsDeviceFileOk).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, OpenConnection).WillOnce(Return(true));

    obdAccess.SetDevice(std::move(CreateUsbDevice()));

    ASSERT_TRUE(obdAccess.Connect());
    ASSERT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Connected);

    EXPECT_CALL(obdAccess, Transaction("abc")).WillOnce(Return(std::string("def")));

    std::string response = obdAccess.Transaction("abc");
    EXPECT_EQ(response, "def");
    EXPECT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Connected);
}

TEST_F(UsbAccess_F, Reconnect_Default)
{
    EXPECT_CALL(obdAccess, IsDeviceFileOk).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, OpenConnection).WillOnce(Return(true));
    EXPECT_TRUE(obdAccess.Connect());
    EXPECT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Connected);

    EXPECT_CALL(obdAccess, IsFileDescriptorValid).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, CloseConnection).WillOnce(Return(true));
    EXPECT_TRUE(obdAccess.Disconnect());
    EXPECT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Disconnected);

    EXPECT_CALL(obdAccess, IsDeviceFileOk).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, OpenConnection).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, IsFileDescriptorValid).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, CloseConnection).WillOnce(Return(true));

    EXPECT_TRUE(obdAccess.Reconnect());
    EXPECT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Connected);
}

TEST(UsbAccess, InvalidDevice)
{
    Obd::UsbObdAccess OBD;

    EXPECT_THROW(
        {
            OBD.SetDevice(std::move(CreateBluetoothDevice()));
        },
        std::logic_error);
}

TEST(UsbAccess, NoDeviceFile)
{
    Obd::UsbObdAccess OBD;
    OBD.SetDevice(std::move(CreateUsbDevice()));
    EXPECT_FALSE(OBD.Connect());
    EXPECT_EQ(OBD.GetConnectionStatus(), Obd::ConnectionStatus::DeviceNotFound);
}

TEST(UsbAccess, NoDeviceSet)
{
    Obd::UsbObdAccess OBD;
    EXPECT_FALSE(OBD.Connect());
    EXPECT_EQ(OBD.GetConnectionStatus(), Obd::ConnectionStatus::DeviceNotFound);
}

#endif // SERIAL_OBD_ACCESS_TEST_H_