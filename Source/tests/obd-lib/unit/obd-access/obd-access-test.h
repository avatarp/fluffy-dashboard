#ifndef OBD_ACCESS_TEST_H_
#define OBD_ACCESS_TEST_H_

#include "obd-access.hpp"

#include <gtest/gtest.h>

#include <iostream>

using namespace testing;

class ObdAccessTestClass : public Obd::ObdAccess {
    std::string m_returnedString { "" };
    std::string m_writeCommand { "" };

    // dummies
    bool IsDeviceFileOk() override { return true; }
    bool OpenConnection() override { return true; }
    bool Connect() override { return true; }
    std::string Read() override { return m_returnedString; }
    bool Write(const std::string& command) override
    {
        m_writeCommand = command;
        return true;
    }

public:
    virtual ~ObdAccessTestClass() = default;

    void SetDevice(Obd::Device device) override { m_Device = device; }

    void setDeviceFileDescriptor(int deviceFileDescriptor)
    {
        m_DeviceFileDescriptor = deviceFileDescriptor;
    }

    bool fileDescriptorValidForward()
    {
        return this->IsFileDescriptorValid();
    }

    void setReturnedString(std::string string)
    {
        m_returnedString = string;
    }

    std::string getWriteCommand()
    {
        return m_writeCommand;
    }
};

class ObdAccess_F : public ::testing::Test {
protected:
    ObdAccessTestClass obdAccess;
};

TEST_F(ObdAccess_F, Transaction)
{
    std::string result { "test result" };
    std::string command { "test command" };
    obdAccess.setReturnedString(result);
    EXPECT_EQ(obdAccess.Transaction(command), result);
    EXPECT_EQ(obdAccess.getWriteCommand(), command);
}

TEST_F(ObdAccess_F, DeviceFileDescriptorOk)
{
    obdAccess.setDeviceFileDescriptor(0);
    EXPECT_FALSE(obdAccess.fileDescriptorValidForward());
    obdAccess.setDeviceFileDescriptor(1);
    EXPECT_FALSE(obdAccess.fileDescriptorValidForward());
    obdAccess.setDeviceFileDescriptor(2);
    EXPECT_FALSE(obdAccess.fileDescriptorValidForward());
}

TEST_F(ObdAccess_F, Disconnect)
{
    obdAccess.setDeviceFileDescriptor(0);
    EXPECT_TRUE(obdAccess.Disconnect());
}

TEST_F(ObdAccess_F, GetDevice)
{
    Obd::Device device { "test", Obd::ConnectionType::Bluetooth, "test" };
    obdAccess.SetDevice(device);
    EXPECT_EQ(obdAccess.GetDevice().m_DeviceFilePath, device.m_DeviceFilePath);
    EXPECT_EQ(obdAccess.GetDevice().m_ConnectionType, device.m_ConnectionType);
    EXPECT_EQ(obdAccess.GetDevice().m_Description, device.m_Description);
}

#endif // OBD_ACCESS_TEST_H_