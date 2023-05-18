#pragma once
#include <gtest/gtest.h>
#include "obd-access-utils.h"

using namespace testing;

TEST(BluetoothAccess, DataTransferOk)
{
    PipesEnv pipe;
    Obd::BluetoothObdAccess OBD;
    OBD.SetDevice(CreateBluetoothDevice());

    ASSERT_TRUE(OBD.Connect());
    ASSERT_EQ(OBD.GetConnectionStatus(), Obd::ConnectionStatus::Connected);

    std::string response = OBD.Transaction("abc");
    EXPECT_EQ(response, "abc");
    EXPECT_EQ(OBD.GetConnectionStatus(), Obd::ConnectionStatus::Connected);
}

TEST(BluetoothAccess, InvalidDevice)
{
    Obd::BluetoothObdAccess OBD;

    EXPECT_THROW({
                     OBD.SetDevice(CreateUsbDevice());
                 }, std::logic_error);
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

TEST(BluetoothAccess, Reconnect)
{
    PipesEnv pipe;
    Obd::BluetoothObdAccess OBD;
    OBD.SetDevice(std::move(CreateBluetoothDevice()));

    EXPECT_TRUE(OBD.Connect());
    EXPECT_EQ(OBD.GetConnectionStatus(),Obd::ConnectionStatus::Connected);

    OBD.CloseConnection();
    EXPECT_EQ(OBD.GetConnectionStatus(), Obd::ConnectionStatus::Disconnected);

    EXPECT_TRUE(OBD.Reconnect());
    EXPECT_EQ(OBD.GetConnectionStatus(),Obd::ConnectionStatus::Connected);
}
