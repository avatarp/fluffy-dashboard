#pragma once
#include <gtest/gtest.h>
#include "obd-access-utils.h"

using namespace testing;

TEST(UsbAccess, DataTransferOk)
{
    PipesEnv pipe;
    Obd::UsbObdAccess OBD;
    OBD.SetDevice(std::move(CreateUsbDevice()));

    ASSERT_TRUE(OBD.Connect());
    ASSERT_EQ(OBD.GetConnectionStatus(),Obd::ConnectionStatus::Connected);

    std::string response = OBD.Transaction("abc");
    EXPECT_EQ(response, "abc");
    EXPECT_EQ(OBD.GetConnectionStatus(),Obd::ConnectionStatus::Connected);
}

TEST(UsbAccess, InvalidDevice)
{
    Obd::UsbObdAccess OBD;

    EXPECT_THROW(
    {
    OBD.SetDevice(std::move(CreateBluetoothDevice()));
                },std::logic_error);
}

TEST(UsbAccess, NoDeviceFile)
{
    Obd::UsbObdAccess OBD;
    OBD.SetDevice(std::move(CreateUsbDevice()));
    EXPECT_FALSE(OBD.Connect());
    EXPECT_EQ(OBD.GetConnectionStatus(),Obd::ConnectionStatus::DeviceNotFound);
}

TEST(UsbAccess, NoDeviceSet)
{
    Obd::UsbObdAccess OBD;
    EXPECT_FALSE(OBD.Connect());
    EXPECT_EQ(OBD.GetConnectionStatus(),Obd::ConnectionStatus::DeviceNotFound);

}

TEST(UsbAccess, Reconnect)
{
    PipesEnv pipe;
    Obd::UsbObdAccess OBD;
    OBD.SetDevice(std::move(CreateUsbDevice()));

    EXPECT_TRUE(OBD.Connect());
    EXPECT_EQ(OBD.GetConnectionStatus(),Obd::ConnectionStatus::Connected);

    OBD.CloseConnection();
    EXPECT_EQ(OBD.GetConnectionStatus(), Obd::ConnectionStatus::Disconnected);

    EXPECT_TRUE(OBD.Reconnect());
    EXPECT_EQ(OBD.GetConnectionStatus(),Obd::ConnectionStatus::Connected);
}
