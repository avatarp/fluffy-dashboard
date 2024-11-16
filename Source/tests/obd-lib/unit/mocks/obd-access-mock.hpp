#ifndef OBD_ACCESS_MOCK_HPP_
#define OBD_ACCESS_MOCK_HPP_

#include "bluetooth-obd-access.hpp"
#include "serial-obd-access.hpp"

#include <gmock/gmock.h>

struct MockBtAccess : Obd::BluetoothObdAccess {

    MOCK_METHOD(bool, IsDeviceFileOk, ());
    MOCK_METHOD(bool, OpenConnection, ());

    MOCK_METHOD(bool, Write, (const std::string&));
    MOCK_METHOD(std::string, Read, ());
    MOCK_METHOD(std::string, Transaction, (const std::string&));
};

struct MockUsbAccess : Obd::UsbObdAccess {

    MOCK_METHOD(bool, IsDeviceFileOk, ());
    MOCK_METHOD(bool, OpenConnection, ());

    MOCK_METHOD(bool, Write, (const std::string&));
    MOCK_METHOD(std::string, Read, ());
    MOCK_METHOD(std::string, Transaction, (const std::string&));
};

#endif // OBD_ACCESS_MOCK_HPP_