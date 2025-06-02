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

#include "spdlog/spdlog.h"

namespace Obd {

constexpr uint8_t stderrFileDescriptor { 2 };
const uint16_t bufferSize = 256;

enum class ConnectionStatus {
    Disconnected,
    Connected,
    DeviceTimeout,
    DeviceNotFound,
    ConnectionLost
};

inline void logErrno(const std::string& message)
{
    constexpr size_t errBufferSize = 1024;
    std::array<char, errBufferSize> errBuffer {};
    spdlog::error(message + ' ' + strerror_r(errno, errBuffer.data(), errBufferSize));
    errno = 0;
}

class ObdAccess {
protected:
    Device m_Device {};
    ConnectionStatus m_ConnectionStatus { ConnectionStatus::Disconnected };
    termios m_Terminal {};
    int m_DeviceFileDescriptor {};

    virtual bool IsDeviceFileOk() = 0;
    virtual bool OpenConnection() = 0;
    virtual bool CloseConnection();
    virtual bool IsFileDescriptorValid();

public:
    ObdAccess() = default;
    virtual ~ObdAccess();

    const Device& GetDevice() const;
    virtual void SetDevice(Device device) = 0;

    virtual bool Connect() = 0;
    virtual bool Disconnect();
    bool Reconnect();

    const ConnectionStatus& GetConnectionStatus() const;

    virtual std::string Read() = 0;
    virtual bool Write(const std::string& command) = 0;
    std::string Transaction(const std::string& command);
};
}

#endif // OBD_ACCESS_HPP_
