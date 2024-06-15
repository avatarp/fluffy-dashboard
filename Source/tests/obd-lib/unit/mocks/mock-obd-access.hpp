#ifndef MOCK_OBD_ACCESS_HPP_
#define MOCK_OBD_ACCESS_HPP_

#include "bluetooth-obd-access.hpp"
#include "serial-obd-access.hpp"

#include <gmock/gmock.h>

struct MockBtAccess : Obd::BluetoothObdAccess {

    MOCK_METHOD(bool, Connect, ());
    MOCK_METHOD(const Obd::ConnectionStatus, GetConnectionStatus, ());

    MOCK_METHOD(bool, Write, (const std::string&));
    MOCK_METHOD(std::string, Read, ());
    MOCK_METHOD(std::string, Transaction, (const std::string&));
};

struct MockSerialAccess : Obd::UsbObdAccess {
    MOCK_METHOD(bool, Connect, ());
    MOCK_METHOD(const Obd::ConnectionStatus, GetConnectionStatus, ());
    MOCK_METHOD(bool, Write, (const std::string&));
    MOCK_METHOD(std::string, Read, ());
    MOCK_METHOD(std::string, Transaction, (const std::string&));
};

#endif // MOCK_OBD_ACCESS_HPP_