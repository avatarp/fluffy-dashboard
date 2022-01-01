#pragma once
#include <gtest/gtest.h>
#include "obd-access-utils.h"

using namespace testing;

TEST(DataTransferOk,BluetoothAccess)
{
    SetupLoopbackEnvironment();
    Obd::BluetoothObdAccess OBD;
    OBD.SetDevice(std::move(CreateBluetoothDevice()));

    ASSERT_TRUE(OBD.Connect());
    ASSERT_EQ(OBD.GetConnectionStatus(),Obd::ConnectionStatus::Connected);

    std::string response = OBD.Transaction("abc");
    EXPECT_EQ(response, "abc");
    EXPECT_EQ(OBD.GetConnectionStatus(),Obd::ConnectionStatus::Connected);
}

TEST(InvalidDevice, BluetoothAccess)
{
    CleanupEnvironment();
    Obd::BluetoothObdAccess OBD;

    EXPECT_THROW(
    {
                    OBD.SetDevice(std::move(CreateUsbDevice()));
                },std::logic_error);
}

TEST(NoDeviceFile, BluetoothAccess)
{
    CleanupEnvironment();
    Obd::BluetoothObdAccess OBD;
    OBD.SetDevice(std::move(CreateBluetoothDevice()));
    EXPECT_FALSE(OBD.Connect());
    EXPECT_EQ(OBD.GetConnectionStatus(),Obd::ConnectionStatus::DeviceNotFound);
}

TEST(NoDeviceSet, BluetoothAccess)
{
    Obd::BluetoothObdAccess OBD;
    EXPECT_FALSE(OBD.Connect());
    EXPECT_EQ(OBD.GetConnectionStatus(),Obd::ConnectionStatus::DeviceNotFound);

}

TEST(Reconnect, BluetoothAccess)
{
    SetupLoopbackEnvironment();
    Obd::BluetoothObdAccess OBD;
    OBD.SetDevice(std::move(CreateBluetoothDevice()));

    EXPECT_TRUE(OBD.Connect());
    EXPECT_EQ(OBD.GetConnectionStatus(),Obd::ConnectionStatus::Connected);

    EXPECT_TRUE(OBD.Reconnect());
    EXPECT_EQ(OBD.GetConnectionStatus(),Obd::ConnectionStatus::Connected);
}
