#ifndef OBD_ACCESS_HPP_
#define OBD_ACCESS_HPP_

#include "device.hpp"
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <termios.h>
#include <unistd.h>

namespace Obd {

const uint16_t bufferSize = 256;

enum class ConnectionStatus {
    Disconnected,
    Connected,
    DeviceTimeout,
    DeviceNotFound,
    ConnectionLost
};

class ObdAccess {
protected:
    Device m_Device {};
    ConnectionStatus m_ConnectionStatus { ConnectionStatus::Disconnected };
    termios m_Terminal {};
    int m_DevicePort {};

    virtual bool IsDeviceFileOk() = 0;
    virtual bool OpenConnection() = 0;

public:
    ObdAccess() = default;
    virtual ~ObdAccess();
    virtual void SetDevice(Device device) = 0;
    virtual bool Connect() = 0;
    virtual bool CloseConnection();
    bool Reconnect();
    const Device& GetDevice() const;
    const ConnectionStatus& GetConnectionStatus() const;
    virtual bool Write(const std::string& command) = 0;
    virtual std::string Read() = 0;
    std::string Transaction(const std::string& command);
};
}

#endif // OBD_ACCESS_HPP_
