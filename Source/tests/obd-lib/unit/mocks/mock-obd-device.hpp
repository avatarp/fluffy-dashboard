#ifndef MOCK_OBD_DEVICE_HPP_
#define MOCK_OBD_DEVICE_HPP_

#include "device.hpp"

#include <gmock/gmock.h>

struct MockObdDevice : Obd::Device {
    MOCK_METHOD(std::string, GetDescription, ());
    MOCK_METHOD(Obd::ConnectionType, GetConnectionType, ());
    MOCK_METHOD(std::string, GetDeviceFilePath, ());
};

#endif // MOCK_OBD_DEVICE_HPP_