#pragma once
#include "string"

namespace Obd {

enum class ConnectionType {
    NoConnection,
    Usb,
    Bluetooth
};

class Device {
private:
    std::string m_DeviceFilePath = "";
    ConnectionType m_ConnectionType{ConnectionType::NoConnection};
    std::string m_Description = "";

public:
    Device() = default;
    Device(std::string deviceFilePath,
        ConnectionType connectionType,
        std::string description)
        : m_DeviceFilePath { deviceFilePath }
        , m_ConnectionType { connectionType }
        , m_Description { description }
    {
    }

    std::string GetDescription() const;
    ConnectionType GetConnectionType() const;
    std::string GetDeviceFilePath() const;
};
}
