#ifndef DEVICE_HPP_
#define DEVICE_HPP_

#include "string"

namespace Obd {

enum class ConnectionType {
    NoConnection,
    Serial,
    Bluetooth
};

struct Device {
    std::string m_DeviceFilePath = "";
    ConnectionType m_ConnectionType { ConnectionType::NoConnection };
    std::string m_Description = "";

    Device() = default;
    Device(std::string deviceFilePath,
        ConnectionType connectionType,
        std::string description)
        : m_DeviceFilePath { deviceFilePath }
        , m_ConnectionType { connectionType }
        , m_Description { description }
    {
    }
};
}

#endif // DEVICE_HPP_