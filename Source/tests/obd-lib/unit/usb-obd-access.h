#ifndef USB_OBD_ACCESS_H_
#define USB_OBD_ACCESS_H_

#include "serial-obd-access.hpp"

#include "mocks/mock-obd-access.hpp"
#include "mocks/mock-obd-device.hpp"
#include "obd-access-utils.h"
#include <gtest/gtest.h>

using namespace testing;

class UsbAccess_F : public ::testing::Test {
protected:
    MockUsbAccess obdAccess {};

    void SetUp()
    {
        EXPECT_CALL(obdAccess, IsDeviceFileOk).WillOnce(Return(true));
        EXPECT_CALL(obdAccess, OpenConnection).WillOnce(Return(true));
    }
};

TEST_F(UsbAccess_F, DataTransferOk)
{
    obdAccess.SetDevice(std::move(CreateUsbDevice()));

    ASSERT_TRUE(obdAccess.Connect());
    ASSERT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Connected);

    EXPECT_CALL(obdAccess, Transaction("abc")).WillOnce(Return(std::string("def")));

    std::string response = obdAccess.Transaction("abc");
    EXPECT_EQ(response, "def");
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

TEST_F(UsbAccess_F, Reconnect)
{
    obdAccess.SetDevice(std::move(CreateUsbDevice()));

    EXPECT_TRUE(obdAccess.Connect());
    EXPECT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Connected);

    EXPECT_CALL(obdAccess, IsDeviceFileOk).WillOnce(Return(true));
    EXPECT_CALL(obdAccess, OpenConnection).WillOnce(Return(true));

    EXPECT_TRUE(obdAccess.Reconnect());
    EXPECT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Connected);

    obdAccess.CloseConnection();
    EXPECT_EQ(obdAccess.GetConnectionStatus(), Obd::ConnectionStatus::Disconnected);
}

#endif // USB_OBD_ACCESS_H_