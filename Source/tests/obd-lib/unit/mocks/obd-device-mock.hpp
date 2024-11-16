#ifndef OBD_DEVICE_MOCK_HPP_
#define OBD_DEVICE_MOCK_HPP_

#include "device.hpp"

#include <gmock/gmock.h>

struct MockObdDevice : Obd::Device {
    MOCK_METHOD(std::string, GetDescription, ());
    MOCK_METHOD(Obd::ConnectionType, GetConnectionType, ());
    MOCK_METHOD(std::string, GetDeviceFilePath, ());
};

#endif // OBD_DEVICE_MOCK_HPP_